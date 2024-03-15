#include <stdio.h>

int int_size_is_32_b() {
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}

int int_size_is_32_c() {
    int set_msb = ((1 << 15) << 15) << 1;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}

int main() {
    printf("%d\n", int_size_is_32_b());
    printf("%d\n", int_size_is_32_c());
}
