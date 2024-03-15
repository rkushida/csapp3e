#include <assert.h>

int a(int x) {
    return !(x + 1);
}

int b(int x) {
    return a(~x);
}

int c(int x) {
    return !((x + 1) & 0xFF);
}

int d(int x) {
    return c(~x >> ((sizeof(int) - 1) << 3));
}

int main() {
    assert(a(0xFFFFFFFF) == 1);
    assert(a(0xFFFF00FF) == 0);
    assert(b(0x00000000) == 1);
    assert(b(0x0000FF00) == 0);
    assert(c(0xFFFFFFFF) == 1);
    assert(c(0xFFFFFF00) == 0);
    assert(d(0x00FFFFFF) == 1);
    assert(d(0xFFFFFFFF) == 0);
}
