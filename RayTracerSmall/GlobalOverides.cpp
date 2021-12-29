#include "GlobalOverides.h"

void operator delete(void* memory)
{
	MemoryManagerRef::memoryManager->genMemPool->FreeMemory(memory);
}

void* operator new(size_t size)
{
	return MemoryManagerRef::memoryManager->genMemPool->Allocate(size);
}