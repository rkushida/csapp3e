#include <math.h>

float u2f(unsigned f) {
    return *(float *)&f;
}

int equal(float x, float y) {
    int xisnan = isnan(x);
    int yisnan = isnan(y);
    return (xisnan || yisnan) ? xisnan == yisnan : x == y;
}
