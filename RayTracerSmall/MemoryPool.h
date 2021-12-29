#ifndef _MEMORY_POOL_H_

#include "Chunk.h"
using namespace std;
#include <iostream>

class MemoryPool
{
public:

	int AmountOfMemoryUsed();

	void* Allocate(size_t varSize);
	void FreeMemory(void* freevar);

	void operator delete(void* poolMemory);
	void* operator new(size_t poolsize);

	unsigned char* HmemPool;
	size_t HsizeOfChunk;
	
	Chunk* FirstChunk;

	int HusedBytes;
	int Hallocatedmemory;
	int HmaxMem;

	MemoryPool(size_t PoolSizeBytes);
	~MemoryPool();

};

struct MemoryHeader
{
	int MPerrorCheck;
	int MPsizeOfVariable;	
};

struct MemoryFooter
{

};


#endif