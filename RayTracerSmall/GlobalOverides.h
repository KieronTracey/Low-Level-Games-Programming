#ifndef _GLOBAL_OVERIDES_H_
#define _GLOBAL_OVERIDES_H_
#include <iostream>
#include "MemoryManager.h"

using namespace std;

void* operator new(size_t size);
void operator delete(void* pMem);

#endif
