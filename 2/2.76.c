#include <stdlib.h>
#include <string.h>
#include <assert.h>

void *_calloc(size_t nmemb, size_t size) {
    if (!nmemb || !size) return NULL;
    size_t total_size = size * nmemb;
    char *buf = malloc(total_size);
    memset(buf, 0, total_size);
    return (void *)buf;
}

int main() {
    char *buf = _calloc(2, 1);
    assert(!buf[0]);
    assert(buf[0] == buf[1]);
}
