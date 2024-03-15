#define IDENT 0
#define OP +

typedef long data_t;

typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

vec_ptr new_vec(long len);

int get_vec_element(vec_ptr v, long index, data_t *dest);

long vec_length(vec_ptr v);
