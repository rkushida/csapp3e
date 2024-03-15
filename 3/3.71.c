#include <stdio.h>

#define size 10

void good_echo() {
    char buf[size];
    while (fgets(buf, size, stdin) != NULL) {
        printf("%s", buf);
    }
}

int main() {
    good_echo();
}
