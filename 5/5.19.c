void psum1(float a[], float p[], long n) {
    long i;
    long sum = a[0];
    p[0] = a[0];
    for (i = 1; i < n; i++) {
        sum += a[i];
        p[i] = sum;
    }
}

void effective_psum1(float a[], float p[], long n) {
    long i;
    float sum = 0;
    float c0;
    float c1;
    float c2;
    float c3;
    for (i = 0; i + 3 < n; i += 4) {
        sum += (a[i] + a[i+1] + a[i+2] + a[i+3]);
        c0 = sum + a[i];
        c1 = c0 + a[i+1];
        c2 = c1 + a[i+2];
        c3 = c2 + a[i+3];
        p[i] = c0;
        p[i+1] = c1;
        p[i+2] = c2;
        p[i+3] = c3;
    }
    for (; i < n; i++) {
        c3 += a[i];
        p[i] = c3;
    }
}
