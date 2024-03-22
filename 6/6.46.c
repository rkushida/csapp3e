#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 1024
#define n 128

void col_convert(int *G, int dim) {
    int i, j;

    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            G[j*dim + i] = G[j*dim + i] || G[i*dim + j];
        }
    }
}

void effective_col_convert(int *G, int dim) {
    for (int i = 0; i + n <= dim; i += n) {
        for (int j = 0; j + n <= dim; j += n) {
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    G[(j+l)*dim + (i+k)] |= G[(i+k)*dim + (j+l)];
                }
            }
        }
    }
    int c = (dim / n) * n;
    for (int i = 0; i < c; i++) {
        for (int j = c; j < dim; j++) {
            G[j*dim + i] |= G[i*dim + j];
        }
    }
    for (int i = c; i < dim; i++) {
        for (int j = 0; j < c; j++) {
            G[j*dim + i] |= G[i*dim + j];
        }
    }
    for (int i = c; i < dim; i++) {
        for (int j = c; j < dim; j++) {
            G[j*dim + i] |= G[i*dim + j];
        }
    }
}

void set(int *G, int dim) {
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            G[i*dim + j] = (i == j) ? 1 : rand() % 2;
        }
    }
}

void test() {
    int size = N * N;
    int G[size];
    int H[size];
    int I[size];
    set(G, N);
    memcpy(H, G, sizeof(int) * N * N);
    memcpy(I, G, sizeof(int) * N * N);
    col_convert(H, N);
    effective_col_convert(I, N);
    for (int i = 0; i < size; i++) {
        assert(H[i] == I[i]);
    }
}

void measure() {
    int size = N * N;
    int G[size];
    clock_t start, end, duration = 0;
    for (int i = 0; i < 1000; i++) {
        set(G, N);
        start = clock();
        effective_col_convert(G, N);
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
