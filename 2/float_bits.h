#define SIGN_BIT_SIZE 1
#define EXP_BIT_SIZE 8
#define FRAC_BIT_SIZE 23

#define SIGN_BIT_MASK ((1 << SIGN_BIT_SIZE) - 1)
#define EXP_BIT_MASK ((1 << EXP_BIT_SIZE) - 1)
#define FRAC_BIT_MASK ((1 << FRAC_BIT_SIZE) - 1)

#define SIGN(x) ((x >> (EXP_BIT_SIZE + FRAC_BIT_SIZE)) & SIGN_BIT_MASK)
#define EXP(x) ((x >> FRAC_BIT_SIZE) & EXP_BIT_MASK)
#define FRAC(x) (x & FRAC_BIT_MASK)

#define PACK(sign, exp, frac) ((sign << (EXP_BIT_SIZE + FRAC_BIT_SIZE)) | (exp << FRAC_BIT_SIZE) | frac)

#define ISNAN(exp, frac) ((exp == EXP_BIT_MASK) && frac)

typedef unsigned float_bits;
