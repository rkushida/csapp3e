#include <assert.h>

unsigned f2u(float x) {
    return *(unsigned *)&x;
}

int float_le(float x, float y) {
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return (ux == uy) || !((ux << 1) || (uy << 1)) || (ux < uy) ^ (sx || sy);
}

int main() {
    assert(float_le(+0.0, -0.0));
    assert(float_le(1, 2));
    assert(!float_le(2, 1));
    assert(!float_le(-1, -2));
    assert(float_le(-2, -1));
    assert(!float_le(1, -2));
    assert(float_le(-2, 1));
    assert(float_le(0.0, 1));
    assert(float_le(-0.0, 1));
    assert(!float_le(1, 0.0));
    assert(!float_le(1, -0.0));
    assert(!float_le(0, -1));
    assert(float_le(-1, 0.0));
    assert(float_le(-1, -0.0));
}
