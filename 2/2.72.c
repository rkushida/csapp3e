#include <string.h>
#include <assert.h>

void copy_int(int val, void *buf, int maxbytes) {
    if (maxbytes >= (int)sizeof(val)) {
        memcpy(buf, (void *)&val, sizeof(val));
    }
}

int main() {
    int size = 32;
    int buf[size];
    int val = 272;
    memset(buf, 0, sizeof(int) * size);
    copy_int(val, buf, 2);
    copy_int(val, buf + 1, 4);
    copy_int(val, buf + 2, 8);
    assert(buf[0] != val);
    assert(buf[1] == val);
    assert(buf[2] == val);
}
