#include "vec.h"

void inner6(vec_ptr u, vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(u);
    long limit = length - 5;
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;

    for (i = 0; i < limit; i += 6) {
        data_t uv0 = udata[i] * vdata[i];
        data_t uv1 = udata[i+1] * vdata[i+1];
        data_t uv2 = udata[i+2] * vdata[i+2];
        data_t uv3 = udata[i+3] * vdata[i+3];
        data_t uv4 = udata[i+4] * vdata[i+4];
        data_t uv5 = udata[i+5] * vdata[i+5];
        sum = (((((sum + uv0) + uv1) + uv2) + uv3) + uv4) + uv5;
    }

    for (; i < length; i++) {
        sum = sum + udata[i] * vdata[i];
    }

    *dest = sum;
}
