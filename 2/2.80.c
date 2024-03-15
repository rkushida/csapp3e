#include <limits.h>
#include <assert.h>

int threefourths(int x) {
    int bias = (x >> ((sizeof(int) << 3) - 1)) & 0x3;
    int quarter = (x + bias) >> 2;
    return quarter + (quarter << 1);
}

int check(int x) {
    return threefourths(x) == (x / 4 * 3);
}

int main() {
    assert(check(3));
    assert(check(-6));
    assert(check(0));
    assert(check(INT_MIN));
    assert(check(INT_MAX));
}
