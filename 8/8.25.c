#include "csapp.h"

sigjmp_buf buf;

void handler() {
    siglongjmp(buf, 1);
}

char *tfgets(char *__restrict__ __s, int __n, FILE *__restrict__ __stream) {
    if (!sigsetjmp(buf, 1)) {
        Signal(SIGCHLD, handler);
        pid_t pid;
        if ((pid = Fork()) == 0) {
            Sleep(5);
            exit(0);
        } else {
            fgets(__s, __n, __stream);
            Signal(SIGCHLD, SIG_DFL);
            return __s;
        }
    } else {
        return NULL;
    }
}

int main() {
    int n = 32;
    char s[n];
    char *t = tfgets(s, n, stdin);
    if (t == NULL) {
        printf("NULL\n");
    } else {
        printf("%s", t);
    }
}
