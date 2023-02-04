#include "recalloc.h"
#include <string.h>

void* recalloc(void* ptr, size_t num, size_t sizeofType) {
    int bytes = sizeof(*ptr) / sizeofType;

    void* ptr2 = calloc(num, sizeofType);
    memccpy(ptr2, ptr, bytes, sizeofType);
    free(ptr);
    return ptr2;
}