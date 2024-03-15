#include <assert.h>

unsigned replace_byte(unsigned x, int i, unsigned char b) {
    int shift = i << 3;
    return ((x & ~(0xFF << shift)) | (b << shift));
}

int main() {
    assert(replace_byte(0x12345678, 2, 0xAB) == 0x12AB5678);
    assert(replace_byte(0x12345678, 0, 0xAB) == 0x123456AB);
}
