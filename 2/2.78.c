#include <assert.h>

int divide_power2(int x, int k) {
    int bias = (x >> ((sizeof(int) << 3) - 1)) & ((1 << k) - 1);
    return (x + bias) >> k;
}

int check(int x, int k) {
    return divide_power2(x, k) == (x / (1 << k));
}

int main() {
    assert(check(13, 2));
    assert(check(-15, 3));
    assert(check(0, 1));
}
