#include <stdio.h>

int int_shifts_are_arithmetic() {
    return (~0 >> ((sizeof(int) << 3) - 1) & 1);
}


int main() {
    printf("%d\n", int_shifts_are_arithmetic());
}
