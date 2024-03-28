#include "csapp.h"
#define MAXARGS 128
#define JOB_STOPPING 0
#define JOB_RUNNING 1
#define UNDEFINED_VARIABLE(x) (void)(x)

void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

struct Job {
    pid_t jid;
    pid_t pid;
    int status;
    char cmdline[MAXLINE];
    struct Job *next;
};

struct Job *joblist;
volatile sig_atomic_t fgpid = 0;
sigjmp_buf buf;

struct Job *createjob(int jid, pid_t pid, char *cmdline) {
    struct Job *job = (struct Job *)malloc(sizeof(struct Job));
    job->jid = jid;
    job->pid = pid;
    job->status = JOB_RUNNING;
    strcpy(job->cmdline, cmdline);
    job->next = NULL;
    return job;
}

void printjob(struct Job *job, int all) {
    printf("[%d] %d ", job->jid, job->pid);
    if (all) {
        char *status = job->status == JOB_RUNNING ? "Running": "Stopped";
        printf("%s\t", status);
    }
    printf("%s", job->cmdline);
}

void initjobs() {
    joblist = createjob(0, 0, "");
}

struct Job *addjob(pid_t pid, char *cmdline) {
    struct Job *cur = joblist;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = createjob(cur->jid + 1, pid, cmdline);
    return cur->next;
}

void deletejob(pid_t pid) {
    struct Job *cur = joblist;
    while (cur->next != NULL) {
        if (cur->next->pid == pid) {
            struct Job *tmp = cur->next;
            cur->next = cur->next->next;
            Free((void *)tmp);
            return;
        }
        cur = cur->next;
    }
}

void stopjob(pid_t pid) {
    struct Job *cur = joblist;
    while (cur != NULL) {
        if (cur->pid == pid) {
            cur->status = JOB_STOPPING;
            return;
        }
        cur = cur->next;
    }
}

int parsejob(char *job, int *id) {
    if (!strncmp(job, "%%", 1)) {
        *id = atoi(++job);
        return 0;
    } else {
        *id = atoi(job);
        return 1;
    }
}

pid_t getjobpid(pid_t jid) {
    struct Job *current = joblist;
    while (current != NULL) {
        if (current->jid == jid) {
            return current->pid;
        }
        current = current->next;
    }
    return 0;
}

pid_t getjobjid(pid_t pid) {
    struct Job *current = joblist;
    while (current != NULL) {
        if (current->pid == pid) {
            return current->jid;
        }
        current = current->next;
    }
    return 0;
}

void printmsg(int jid, pid_t pid, int sig) {
    Sio_puts("Job ");
    if (jid != 0) {
        Sio_puts("[");
        Sio_putl(jid);
        Sio_puts("]");
        Sio_puts(" ");
    }
    Sio_putl(pid);
    Sio_puts(" ");
    Sio_puts(sig == SIGTSTP ? "stopped" : "terminated");
    Sio_puts(" by signal: ");
    Sio_puts(strsignal(sig));
    Sio_puts("\n");
}

void sigchld_handler() {
    int olderrno = errno;
    sigset_t mask_all, prev_all;
    pid_t pid;
    int status;
    Sigfillset(&mask_all);
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        deletejob(pid);
        Sigprocmask(SIG_SETMASK, &prev_all, NULL);
        if (WIFSIGNALED(status)) {
            printmsg(0, pid, WTERMSIG(status));
        }
        if (fgpid == pid) {
            fgpid = 0;
        }
    }
    errno = olderrno;
}

void sigint_handler() {
    int olderrno = errno;
    Sio_puts("\n");
    if (fgpid != 0) {
        Kill(-fgpid, SIGINT);
    } else {
        siglongjmp(buf, 1);
    }
    errno = olderrno;
}

void sigtstp_handler() {
    int olderrno = errno;
    sigset_t mask_all, prev_all;
    Sigfillset(&mask_all);
    Sio_puts("\n");
    if (fgpid != 0) {
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        pid_t jid = getjobjid(fgpid);
        stopjob(fgpid);
        Sigprocmask(SIG_SETMASK, &prev_all, NULL);
        Kill(-fgpid, SIGTSTP);
        printmsg(jid, fgpid, SIGTSTP);
        fgpid = 0;
    } else {
        siglongjmp(buf, 1);
    }
    errno = olderrno;
}

int count_argv(char **argv) {
    int c = 0;
    while (argv[c] != NULL) {
        c++;
    }
    return c;
}

void jobs() {
    struct Job *cur = joblist->next;
    while (cur != NULL) {
        printjob(cur, 1);
        cur = cur->next;
    }
}

void fg(char *job) {
    UNDEFINED_VARIABLE(job);
}

void bg(char *job) {
    int id;
    int proc = parsejob(job, &id);
    if (id == 0) {
        return;
    }
    if (proc) {
        Kill(id, SIGCONT);
    } else {
        pid_t pgid = getpgid(id);
        Kill(pgid, SIGCONT);
    }
}

int main() {
    char cmdline[MAXLINE];
    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGINT, sigint_handler);
    Signal(SIGTSTP, sigtstp_handler);
    initjobs();
    while (1) {
        sigsetjmp(buf, 1);
        printf("> ");
        Fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin)) {
            exit(0);
        }
        eval(cmdline);
    }
}

void eval(char *cmdline) {
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;
    sigset_t mask_all, mask_one, prev_one;
    Sigfillset(&mask_all);
    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);
    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL) {
        return;
    }
    if (!builtin_command(argv)) {
        Sigprocmask(SIG_BLOCK, &mask_one, &prev_one);
        if ((pid = Fork()) == 0) {
            Sigprocmask(SIG_SETMASK, &prev_one, NULL);
            Setpgid(0, 0);
            if (execve(argv[0], argv, environ) < 0) {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }
        Sigprocmask(SIG_BLOCK, &mask_all, NULL);
        struct Job *job = addjob(pid, cmdline);
        if (!bg) {
            fgpid = pid;
            while (fgpid) {
                Sigsuspend(&prev_one);
            }
        } else {
            printjob(job, 0);
        }
        Sigprocmask(SIG_SETMASK, &prev_one, NULL);
        return;
    }
}

int builtin_command(char **argv) {
    if (!strcmp(argv[0], "quit")) {
        exit(0);
    }
    if (!strcmp(argv[0], "&")) {
        return 1;
    }
    if (!strcmp(argv[0], "jobs")) {
        jobs();
        return 1;
    }
    if (!strcmp(argv[0], "fg")) {
        if (count_argv(argv) != 2) {
            fprintf(stderr, "usage: %s <job>", argv[0]);
        } else {
            fg(argv[1]);
        }
        return 1;
    }
    if (!strcmp(argv[0], "bg")) {
        if (count_argv(argv) != 2) {
            fprintf(stderr, "usage: %s <job>", argv[0]);
        } else {
            bg(argv[1]);
        }
        return 1;
    }
    return 0;
}

int parseline(char *buf, char **argv) {
    char *delim;
    int argc;
    int bg;
    buf[strlen(buf)-1] = ' ';
    while (*buf && (*buf == ' ')) {
        buf++;
    }
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) {
            buf++;
        }
    }
    argv[argc] = NULL;
    if (argc == 0) {
        return 1;
    }
    if ((bg = (*argv[argc-1] == '&')) != 0) {
        argv[--argc] = NULL;
    }
    return bg;
}
