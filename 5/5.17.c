#include <stddef.h>

void *basic_memset(void *s, int c, size_t n) {
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n) {
        *schar++ = (unsigned char) c;
        cnt++;
    }
    return s;
}

void *effective_memset(void *s, int c, size_t n) {
    size_t cnt = 0;
    unsigned char *schar = s;
    unsigned long *slong;
    unsigned long bytes;
    int k = sizeof(unsigned char);
    for (int i = 0; i < k; i++) {
        ((unsigned char *)&bytes)[i] = (unsigned char)c;
    }
    while ((size_t)schar % k != 0) {
        *schar++ = (unsigned char)c;
        cnt++;
    }
    for (slong = (unsigned long *)schar; cnt + k - 1 < n; cnt += k) {
        *slong = bytes;
        cnt += k;
    }
    for (schar = (unsigned char *)slong; cnt < n; cnt++) {
        *schar = (unsigned char)c;
    }
    return s;
}
