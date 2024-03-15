#include <limits.h>
#include <inttypes.h>
#include <assert.h>

int signed_high_prod(int x, int y) {
    return ((int64_t)x * y) >> (sizeof(int) << 3);
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int set_msb = 1 << ((sizeof(int) << 3) - 1);
    int x_msb = !!(x & set_msb);
    int y_msb = !!(y & set_msb);
    return signed_high_prod(x, y) + x_msb * y + y_msb * x;
}

unsigned _unsigned_high_prod(unsigned x, unsigned y) {
    return ((uint64_t)x * y) >> (sizeof(unsigned) << 3);
}

int check(unsigned x, unsigned y) {
    return unsigned_high_prod(x, y) == _unsigned_high_prod(x, y);
}

int main() {
    assert(check(0x1234, 0xFEDC));
    assert(check(0, 0));
    assert(check(UINT_MAX, 0));
    assert(check(UINT_MAX, UINT_MAX));
}
