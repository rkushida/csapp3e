#include "float.h"

float u2f(unsigned f) {
    return *(float *)&f;
};
