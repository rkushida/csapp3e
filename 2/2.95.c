#include "float_bits.h"
#include "float.h"
#include <assert.h>

float_bits float_half(float_bits f) {
    unsigned sign = SIGN(f);
    unsigned exp = EXP(f);
    unsigned frac = FRAC(f);
    if (ISNAN(exp, frac)) {
        return f;
    }
    unsigned rest = f & ~(1 << (EXP_BIT_SIZE + FRAC_BIT_SIZE));
    int carry = (rest & 3) == 3;
    if (exp == 0) {
        frac = (rest >> 1) + carry;
    } else if (exp == 1) {
        frac = (rest >> 1) + carry;
        exp = EXP(frac);
        frac = FRAC(frac);
    } else if (exp == EXP_BIT_MASK) {
    } else {
        exp -= 1;
    }
    return PACK(sign, exp, frac);
}

int main() {
    LOOP_FLOAT_BITS {
        float test = u2f(float_half(i));
        float ref = u2f(i) / 2;
        assert(equal(test, ref));
    }
}
