#include <assert.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum) {
    int max_bytenum = 3;
    return (int)(word << ((max_bytenum - bytenum) << 3)) >> (max_bytenum << 3);
}

int main() {
    assert(xbyte(0x128934AB, 0) == (int)0xFFFFFFAB);
    assert(xbyte(0x128934AB, 1) == (int)0x00000034);
    assert(xbyte(0x128934AB, 2) == (int)0xFFFFFF89);
    assert(xbyte(0x128934AB, 3) == (int)0x00000012);
}
