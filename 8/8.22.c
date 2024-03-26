#include "csapp.h"
#define UNUSED_VARIABLE(x) (void)(x)

int mysystem(char *command) {
    pid_t pid;
    int status;
    char *sh = "/bin/sh";
    char *argv[] = {sh, "-c", command, NULL};
    if ((pid = Fork()) == 0) {
        Execve(sh, argv, environ);
    } else {
        Waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
    return 0;
}

int main() {
    int c;
    c = mysystem("./exit");
    printf("code: %d\n", c);
    c = mysystem("./pause");
    printf("code: %d\n", c);
}
