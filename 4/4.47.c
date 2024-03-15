#include <stdio.h>
#define SIZE 4

long data[SIZE] = {3, -2, 6, 5};

void bubble_p(long *data, long count) {
    long i, last;
    for (last = count - 1; last > 0; last--) {
        for (i = 0; i < last; i++) {
            if (*(data + i + 1) < *(data + i)) {
                long t = *(data + i + 1);
                *(data + i + 1) = *(data + i);
                *(data + i) = t;
            }
        }
    }
}

int main() {
    bubble_p(data, SIZE);
    for (int i = 0; i < SIZE; i++) {
        printf("%ld ", data[i]);
    }
    printf("\n");
}
