#include "float_bits.h"
#include "float.h"
#include <assert.h>

int float_f2i(float_bits f) {
    unsigned sign = SIGN(f);
    unsigned exp = EXP(f);
    unsigned frac = FRAC(f);
    unsigned int_bit_size = sizeof(int) << 3;
    unsigned bias = (1 << (EXP_BIT_SIZE - 1)) - 1;
    unsigned E = exp - bias;
    unsigned M = (1 << FRAC_BIT_SIZE) | frac;
    unsigned abs = 0;
    if (exp >= (bias + int_bit_size - 1)) {
        abs = 1 << (int_bit_size - 1);
    } else if (exp >= (bias + FRAC_BIT_SIZE)) {
        abs = M << (E - FRAC_BIT_SIZE);
    } else if (exp >= bias) {
        abs = M >> (FRAC_BIT_SIZE - E);
    }
    return (abs ^ -sign) + sign;
}

int main() {
    LOOP_FLOAT_BITS {
        int test = float_f2i(i);
        int ref = (int)u2f(i);
        assert(test == ref);
    }
}
