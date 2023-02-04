#include <stdlib.h>

#if !defined(RECALLOC)
#define RECALLOC

void* recalloc(void* ptr, size_t num, size_t sizeofType);

#endif // RECALLOC