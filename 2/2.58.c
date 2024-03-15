#include <stdio.h>

int is_little_endian() {
    int c = 1;
    int _is_little_endian = *(unsigned char *)&c == 1;
    return _is_little_endian;
}

int main() {
    printf("%d\n", is_little_endian());
}
