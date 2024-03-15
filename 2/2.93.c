#include "float_bits.h"
#include "float.h"
#include <assert.h>
#include <math.h>

float_bits float_absval(float_bits f) {
    unsigned exp = EXP(f);
    unsigned frac = FRAC(f);
    if (ISNAN(exp, frac)) {
        return f;
    }
    return PACK(0, exp, frac);
}

int main() {
    LOOP_FLOAT_BITS {
        float test = u2f(float_absval(i));
        float ref = fabsf(u2f(i));
        assert(equal(test, ref));
    }
}
