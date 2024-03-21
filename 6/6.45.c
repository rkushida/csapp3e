#include <time.h>
#include <stdio.h>
#define N 1024
#define block 1024

void transpose(int *dst, int *src, int dim) {
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            dst[j*dim + i] = src[i*dim + j];
        }
    }
}

void effective_transpose(int *dst, int *src, int dim) {
    for (int i = 0; i < dim; i += block) {
        for (int j = 0; j < dim; j += block) {
            int a = i*dim + j;
            int b = j*dim + i;
            for (int k = 0; k < block; k++) {
                for (int l = 0; l < block; l++) {
                    dst[b + l*dim + k] = src[a + k*dim + l];
                }
            }
        }
    }
}

int main() {
    int count = 1024;
    int size = N * N;
    int src[size], dst[size];
    for (int i = 0; i < size; i++) {
        src[i] = 0;
    }
    clock_t start = clock();
    for (int i = 0; i < count; i++) {
        effective_transpose(dst, src, N);
    }
    clock_t end = clock();
    printf("%d %lf\n", block, (double)(end - start)/CLOCKS_PER_SEC);
}
