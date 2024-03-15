#include <assert.h>
#include <stdio.h>

int a(int x) {
    return x + (x << 4);
}

int b(int x) {
    return x - (x << 3);
}

int c(int x) {
    return (x << 6) - (x << 2);
}

int d(int x) {
    return (x << 4) - (x << 7);
}

int check_all(int x) {
    int a_ok = a(x) == x * 17;
    int b_ok = b(x) == x * -7;
    int c_ok = c(x) == x * 60;
    int d_ok = d(x) == x* -112;
    return a_ok && b_ok && c_ok && d_ok;
}

int main() {
    assert(check_all(3));
    assert(check_all(-5));
    assert(check_all(0));
}
