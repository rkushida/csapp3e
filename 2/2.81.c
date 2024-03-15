#include <assert.h>

unsigned a(unsigned k) {
    return ~0U << k;
}

unsigned b(unsigned k, unsigned j) {
    return ~a(k) << j;
}

int main() {
    assert(a(4) == 0xFFFFFFF0);
    assert(b(4, 8) == 0x00000F00);
}
