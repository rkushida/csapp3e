#include "inner4.h"
#include <stdlib.h>
#include <assert.h>

void inner6(vec_ptr u, vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(u);
    long limit = length - 5;
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum0 = (data_t) 0;
    data_t sum1 = (data_t) 0;
    data_t sum2 = (data_t) 0;
    data_t sum3 = (data_t) 0;
    data_t sum4 = (data_t) 0;
    data_t sum5 = (data_t) 0;

    for (i = 0; i < limit; i += 6) {
        sum0 += udata[i] * vdata[i];
        sum1 += udata[i+1] * vdata[i+1];
        sum2 += udata[i+2] * vdata[i+2];
        sum3 += udata[i+3] * vdata[i+3];
        sum4 += udata[i+4] * vdata[i+4];
        sum5 += udata[i+5] * vdata[i+5];
    }

    for (; i < length; i++) {
        sum0 = sum0 + udata[i] * vdata[i];
    }

    *dest = sum0 + sum1 + sum2 + sum3 + sum4 + sum5;
}

void set(vec_ptr u) {
    for (int i = 0; i < u->len; i++) {
        u->data[i] = (data_t)rand();
    }
}

int main() {
    long len = 16;
    vec_ptr u = new_vec(len);
    vec_ptr v = new_vec(len);
    data_t dest, dest0;
    set(u);
    set(v);
    inner4(u, v, &dest);
    inner6(u, v, &dest0);
    assert(dest == dest0);
}
