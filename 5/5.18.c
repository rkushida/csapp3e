#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

double poly(double a[], double x, long degree) {
    long i;
    double result = a[0];
    double xpwr = x;
    for (i = 1; i <= degree; i++) {
        result += a[i] * xpwr;
        xpwr = x * xpwr;
    }
    return result;
}

double poly63a(double a[], double x, long degree) {
    long i;
    double xpwr0 = 1;
    double xpwr1 = x * x;
    double xpwr2 = x * x * x * x;
    double xpwr = x * x * x * x * x * x;
    double result0 = 0;
    double result1 = 0;
    double result2 = 0;
    for (i = 0; i + 5 <= degree; i += 6) {
        result0 += (a[i] * xpwr0 + a[i+1] * xpwr0 * x);
        result1 += (a[i+2] * xpwr1 + a[i+3] * xpwr1 * x);
        result2 += (a[i+4] * xpwr2 + a[i+5] * xpwr2 * x);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
    }
    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }
    return result0 + result1 + result2;
}

double polyh(double a[], double x, long degree) {
    long i;
    double result = a[degree];
    for (i = degree-1; i >= 0; i--) {
        result = a[i] + x*result;
    }
    return result;
}

double polyh33(double a[], double x, long degree) {
    long i;
    double xpwr0 = 1;
    double xpwr1 = x;
    double xpwr2 = x * x;
    double xpwr = x * x * x;
    double result;
    double result0 = 0;
    double result1 = 0;
    double result2 = 0;
    for (i = degree; i >= 2; i -= 3) {
        result0 = xpwr0*a[i-2] + xpwr*result0;
        result1 = xpwr1*a[i-1] + xpwr*result1;
        result2 = xpwr2*a[i] + xpwr*result2;
    }
    result = result0 + result1 + result2;
    for (; i >= 0; i--) {
        result = a[i] + x*result;
    }
    return result;
}

void set(double *a, long len) {
    for (int i = 0; i < len; i++) {
        a[i] = rand();
    }
}

void test_poly() {
    for (int i = 0; i < 20; i++) {
        double a[i + 1];
        set(a, i + 1);
        double res = poly(a, 2, i);
        double res0 = poly63a(a, 2, i);
        assert(res == res0);
    }
}

void test_polyh() {
    for (int i = 0; i < 20; i++) {
        double a[i + 1];
        set(a, i + 1);
        double res = polyh(a, 2, i);
        double res0 = polyh33(a, 2, i);
        assert(res == res0);
    }
}

int main() {
    test_poly();
    test_polyh();
}
