#include "float_bits.h"
#include "float.h"
#include <assert.h>

float_bits float_negate(float_bits f) {
    unsigned sign = SIGN(f);
    unsigned exp = EXP(f);
    unsigned frac = FRAC(f);
    if (ISNAN(exp, frac)) {
        return f;
    }
    return PACK(~sign, exp, frac);
}

int main() {
    LOOP_FLOAT_BITS {
        float test = u2f(float_negate(i));
        float ref = -u2f(i);
        assert(equal(test, ref));
    }
}
