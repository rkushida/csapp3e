#include "float.h"
#include <math.h>
#include <assert.h>

float fpwr2(int x) {
    unsigned exp, frac;
    unsigned u;

    if (x < -149) {
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        exp = 0;
        frac = 1 << (x + 149);
    } else if (x < 128) {
        exp = x + 127;
        frac = 0;
    } else {
        exp = 255;
        frac = 0;
    }

    u = exp << 23 | frac;
    return u2f(u);
}

int main() {
    for (int i = -150; i < 130; i++) {
        assert(fpwr2(i) == powf(2, i));
    }
}
