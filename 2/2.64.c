#include <assert.h>

int any_odd_one(unsigned x) {
    return !!(x && 0x55555555);
}

int main() {
    assert(any_odd_one(0xFFFFFFFF) == 1);
    assert(any_odd_one(0x00000000) == 0);
    assert(any_odd_one(0x00000001) == 1);
}
