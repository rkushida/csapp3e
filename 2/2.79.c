#include <limits.h>
#include <assert.h>

int mul3div4(int x) {
    int mul3 = x + (x << 1);
    int bias = (mul3 >> ((sizeof(int) << 3) - 1)) & 0x3;
    return (mul3 + bias) >> 2;
}

int check(int x) {
    return mul3div4(x) == (x * 3 / 4);
}

int main() {
    assert(check(3));
    assert(check(-6));
    assert(check(0));
    assert(check(INT_MIN));
    assert(check(INT_MAX));
}
