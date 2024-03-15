#include "float_bits.h"
#include "float.h"
#include <assert.h>

unsigned mask(unsigned x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return x >> 1;
}

unsigned popcnt(unsigned x) {
    x = (x & 0x55555555) + (x >> 1 & 0x55555555);
    x = (x & 0x33333333) + (x >> 2 & 0x33333333);
    x = (x & 0x0f0f0f0f) + (x >> 4 & 0x0f0f0f0f);
    x = (x & 0x00ff00ff) + (x >> 8 & 0x00ff00ff);
    x = (x & 0x0000ffff) + (x >> 16 & 0x0000ffff);
    return x;
}

float_bits float_i2f(int i) {
    unsigned bias = (1 << (EXP_BIT_SIZE - 1)) - 1;
    unsigned int_bit_size = sizeof(int) << 3;
    unsigned round_bit_size = int_bit_size - FRAC_BIT_SIZE;
    unsigned round_bit_mask = (1 << round_bit_size) - 1;
    unsigned round_half = (1 << (round_bit_size - 1));
    unsigned s_round_bit_mask = (round_bit_mask << 1) | round_bit_mask;
    unsigned s_round_half = (round_half << 1) | round_half;
    unsigned sign = (i >> (int_bit_size - 1)) & 1;
    unsigned absval = (i ^ -sign) + sign;
    unsigned bitcnt = popcnt(mask(absval));
    unsigned x = absval << (int_bit_size - bitcnt);
    unsigned exp = (i != 0) ? (bitcnt + bias) : 0;
    unsigned frac = (x >> round_bit_size) & FRAC_BIT_MASK;
    unsigned f = PACK(sign, exp, frac);
    unsigned carry = ((x & round_bit_mask) > round_half) | ((x & s_round_bit_mask) == s_round_half);
    return f + carry;
}

int main() {
    LOOP_FLOAT_BITS {
        float test = u2f(float_i2f(i));
        float ref = (float)(int)i;
        assert(equal(test, ref));
    }
}
