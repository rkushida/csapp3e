#include "csapp.h"
#define N 2

int main() {
    int status, i;
    pid_t pid;

    for (i = 0; i < N; i++) {
        if ((pid = Fork()) == 0) {
            int *addr = (int *)0x200;
            *addr = 0;
        }
    }
    while ((pid = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            char msg[32];
            int n = WTERMSIG(status);
            sprintf(msg, "child %d terminated by signal %d", pid, n);
            psignal(n, msg);
        } else {
            printf("child %d terminated abnormally\n", pid);
        }
    }
    if (errno != ECHILD) {
        unix_error("waitpid error");
    }
}
