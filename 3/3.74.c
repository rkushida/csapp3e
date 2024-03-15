#include "find_range.h"
#include "float.h"
#include <assert.h>

range_t find_range_74(float x) {
    __asm__(
        "vxorps  %xmm1, %xmm1, %xmm1\n\t"
        "vucomiss    %xmm0, %xmm1\n\t"
        "movq   $0, %rax\n\t"
        "movq   $1, %r8\n\t"
        "movq   $2, %r9\n\t"
        "movq   $3, %r10\n\t"
        "cmove  %r8, %rax\n\t"
        "cmovb  %r9, %rax\n\t"
        "cmovp  %r10, %rax"
    );
}

int main() {
    LOOP_FLOAT_BITS {
        float f = u2f(i);
        assert(find_range_74(f) == find_range(f));
    }
}
