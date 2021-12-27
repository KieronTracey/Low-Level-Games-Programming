#include "GlobalOverides.h"

void* operator new(size_t size)
{
	return MemoryManagerRef::mp_memoryManager->mp_genralMemoryPool->Alloc(size);
}

void operator delete(void* pMem)
{
	MemoryManagerRef::mp_memoryManager->mp_genralMemoryPool->Free(pMem);
}