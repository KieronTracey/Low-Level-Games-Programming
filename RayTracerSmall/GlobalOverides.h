#ifndef _GLOBAL_OVERIDES_H_
#define _GLOBAL_OVERIDES_H_
#include "MemoryManager.h"

void operator delete(void* memory);
void* operator new(size_t size);

#endif
