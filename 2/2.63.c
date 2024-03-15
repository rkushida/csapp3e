#include <assert.h>

unsigned srl(unsigned x, int k) {
    unsigned xsra = (int) x >> k;
    int bit_length = sizeof(int) << 3;
    int mask = (1 << (bit_length - k)) - 1;
    return (xsra & mask);
}

unsigned sra(int x, int k) {
    int xsrl = (unsigned) x >> k;
    int bit_length = sizeof(int) << 3;
    int msb = !!(x & (1 << (bit_length - 1)));
    int mask = ((1 << k) - msb) << (bit_length - k);
    return (xsrl | mask);
}

int main() {
    assert(srl(0x87654321, 4) == 0x08765432);
    assert(sra(0x87654321, 4) == 0xF8765432);
    assert(srl(0x12345678, 4) == 0x01234567);
    assert(sra(0x12345678, 4) == 0x01234567);
}
