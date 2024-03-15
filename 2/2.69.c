#include <assert.h>

unsigned rotate_left(unsigned x, int n) {
    return (x << n) | (x >> ((sizeof(int) << 3) - n));
}

int main() {
    assert(rotate_left(0x12345678, 4) == 0x23456781);
    assert(rotate_left(0x12345678, 20) == 0x67812345);
    assert(rotate_left(0x12345678, 0) == 0x12345678);
}
