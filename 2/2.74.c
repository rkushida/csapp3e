#include <limits.h>
#include <assert.h>

int tsub_ok(int x, int y) {
    int z = -y;
    int xz = x + z;
    int set_msb = 1 << ((sizeof(int) << 3) - 1);
    int x_msb = !!(x & set_msb);
    int z_msb = !!(z & set_msb);
    int xz_msb = !!(xz & set_msb);
    int y_is_min = !(y ^ set_msb);
    int positive_overflow = (!x_msb && !!x && !z_msb && !!z && xz_msb) || (!x_msb && y_is_min);
    int negative_overflow = x_msb && z_msb && (!xz_msb || !xz) && !y_is_min;
    return !(positive_overflow | negative_overflow);
}

int main() {
    assert(tsub_ok(1, 2) == 1);
    assert(tsub_ok(1, -2) == 1);
    assert(tsub_ok(-1, 2) == 1);
    assert(tsub_ok(-1, -2) == 1);
    assert(tsub_ok(0, INT_MAX) == 1);
    assert(tsub_ok(0, INT_MIN) == 0);
    assert(tsub_ok(INT_MAX, 0) == 1);
    assert(tsub_ok(INT_MIN, 0) == 1);
    assert(tsub_ok(-1, INT_MAX) == 1);
    assert(tsub_ok(-1, INT_MIN) == 1);
    assert(tsub_ok(INT_MAX, -1) == 0);
    assert(tsub_ok(INT_MIN, -1) == 1);
    assert(tsub_ok(INT_MIN, INT_MIN) == 1);
    assert(tsub_ok(INT_MAX, INT_MAX) == 1);
    assert(tsub_ok(0, 0) == 1);
}
