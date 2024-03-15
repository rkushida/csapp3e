#include <assert.h>
#include <limits.h>

int fits_bits(int x, int n) {
    int msb = !!(x >> ((sizeof(int) << 3) - 1));
    int abs = ((x + msb) ^ -msb) + msb;
    int mask = ~((1 << (n - 1)) - 1);
    return !(abs & mask);
}

int main() {
    assert(fits_bits(7, 4) == 1);
    assert(fits_bits(8, 4) == 0);
    assert(fits_bits(9, 4) == 0);
    assert(fits_bits(-7, 4) == 1);
    assert(fits_bits(-8, 4) == 1);
    assert(fits_bits(-9, 4) == 0);
}
