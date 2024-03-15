#include <stdlib.h>
#include "vec.h"

vec_ptr new_vec(long len) {
    vec_ptr result = (vec_ptr)malloc(sizeof(vec_rec));
    data_t *data = NULL;
    if (!result) {
        return NULL;
    }
    result->len = len;
    if (len > 0) {
        data = (data_t *)calloc(len, sizeof(data_t));
    }
    if (!data) {
        free((void *)result);
        return NULL;
    }
    result->data = data;
    return result;
}

int get_vec_element(vec_ptr v, long index, data_t *dest) {
    if (index < 0|| index >= v->len) {
        return 0;
    }
    *dest = v->data[index];
    return 1;
}

long vec_length(vec_ptr v) {
    return v->len;
}
