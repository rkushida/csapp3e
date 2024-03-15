#include "float_bits.h"
#include "float.h"
#include <assert.h>

float_bits float_twice(float_bits f) {
    unsigned sign = SIGN(f);
    unsigned exp = EXP(f);
    unsigned frac = FRAC(f);
    if (ISNAN(exp, frac)) {
        return f;
    }
    if (exp == 0) {
        frac <<= 1;
        exp = EXP(frac);
    } else if (exp == EXP_BIT_MASK) {
    } else if (exp == (EXP_BIT_MASK - 1)) {
        exp += 1;
        frac = 0;
    } else {
        exp += 1;
    }
    return PACK(sign, exp, frac);
}

int main() {
    LOOP_FLOAT_BITS {
        float test = u2f(float_twice(i));
        float ref = u2f(i) * 2;
        assert(equal(test, ref));
    }
}
