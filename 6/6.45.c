#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define N 1024
#define n 128

void transpose(int *dst, int *src, int dim) {
    int i, j;
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            dst[j*dim + i] = src[i*dim + j];
        }
    }
}

void effective_transpose(int *dst, int *src, int dim) {
    for (int i = 0; i + n <= N; i += n) {
        for (int j = 0; j + n <= N; j += n) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    dst[(j+l)*dim + i+k] = src[(i+k)*dim + j+l];
                }
            }
        }
    }
    int c = (N / n) * n;
    for (int i = 0; i < c; i++) {
        for (int j = c; j < N; j++) {
            dst[j*dim + i] = src[i*dim + j];
        }
    }
    for (int i = c; i < N; i++) {
        for (int j = 0; j < c; j++) {
            dst[j*dim + i] = src[i*dim + j];
        }
    }
    for (int i = c; i < N; i++) {
        for (int j = c; j < N; j++) {
            dst[j*dim + i] = src[i*dim + j];
        }
    }
}

void set(int *array, int length) {
    long mod = (long)1 << 32;
    for (int i = 0; i < length; i++) {
        *array = rand() % mod;
        array++;
    }
}

void test() {
    int size = N * N;
    int src[size], dst[size], dst0[size];
    set(src, size);
    transpose(dst, src, N);
    effective_transpose(dst0, src, N);
    for (int i = 0; i < size; i++) {
        assert(dst[i] == dst0[i]);
    }
}

void measure() {
    int size = N * N;
    int src[size], dst[size];
    clock_t start, end, duration = 0;
    for (int i = 0; i < 1000; i++) {
        set(src, size);
        start = clock();
        effective_transpose(dst, src, N);
        end = clock();
        duration += end - start;
    }
    double duration_in_sec = (double)duration / CLOCKS_PER_SEC;
    printf("N: %d, n: %d => %lf\n", N, n, duration_in_sec);
}

int main() {
    test();
    measure();
}
