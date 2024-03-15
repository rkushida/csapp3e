#include <assert.h>

long combine_byte(long x, long y) {
    return ((x & 0xFF) | (y & ~0xFF));
}

int main() {
    assert(combine_byte(0x89ABCDEF, 0x76543210) == 0x765432EF);
}
