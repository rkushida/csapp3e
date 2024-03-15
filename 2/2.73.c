#include <limits.h>
#include <assert.h>

int saturating_add(int x, int y) {
    int xy = x + y;
    int set_msb = 1 << ((sizeof(int) << 3) - 1);
    int x_msb = !!(x & set_msb);
    int y_msb = !!(y & set_msb);
    int xy_msb = !!(xy & set_msb);
    int overflow = !(x_msb ^ y_msb) && (x_msb ^ xy_msb);
    int overflow_mask = 0 - overflow;
    return (xy & ~overflow_mask) + ((set_msb - !x_msb) & overflow_mask);
}

int main() {
    assert(saturating_add(1, 2) == 3);
    assert(saturating_add(-1, -2) == -3);
    assert(saturating_add(1, -2) == -1);
    assert(saturating_add(-1, 2) == 1);
    assert(saturating_add(INT_MIN, INT_MIN) == INT_MIN);
    assert(saturating_add(INT_MAX, INT_MAX) == INT_MAX);
}
