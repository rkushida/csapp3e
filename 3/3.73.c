#include "find_range.h"
#include "float.h"
#include <assert.h>

range_t find_range_73(float x) {
    __asm__(
        "vxorps  %xmm1, %xmm1, %xmm1\n\t"
        "vucomiss    %xmm0, %xmm1\n\t"
        "jp  .P\n\t"
        "ja  .A\n\t"
        "je  .E\n\t"
        "jb  .B\n"
    ".P:\n\t"
        "movl    $3, %eax\n\t"
        "jmp .Done\n"
    ".A:\n\t"
        "movl    $0, %eax\n\t"
        "jmp .Done\n"
    ".E:\n\t"
        "movl    $1, %eax\n\t"
        "jmp .Done\n"
    ".B:\n\t"
        "movl    $2, %eax\n"
    ".Done:"
    );
}

int main() {
    LOOP_FLOAT_BITS {
        float f = u2f(i);
        assert(find_range_73(f) == find_range(f));
    }
}
