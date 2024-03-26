#include "csapp.h"
#define UNUSED_VARIABLE(x) (void)(x)

int main(int argc, char *argv[], char *envp[]) {
    UNUSED_VARIABLE(argc);
    char *ls = "/bin/ls";
    argv[0] = ls;
    Execve(ls, argv, envp);
}
