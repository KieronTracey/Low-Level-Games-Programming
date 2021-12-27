#ifndef _MEMORY_POOL_H_

#include <iostream>
#include "Chunk.h"

using namespace std;

struct MemoryHeader
{
	int mi_sizeOfVar;
	int mi_errorCheck;
};

struct MemoryFooter
{

};

class MemoryPool
{
public:
	
	MemoryPool(size_t ai_sizeOfPoolInBytes);
	~MemoryPool();

	
	void* Alloc(size_t a_varSize);
	void Free(void* p);
	int AmountOfBytesUsed();

	void* operator new(size_t size);
	void operator delete(void* pMem);

	unsigned char* mp_memPool;
	size_t mi_sizeOfChunk;
	int mi_usedBytes;
	int mi_allocatedBytes;
	int mi_maxBytes;
	Chunk* mp_initalChunk;

};
#endif