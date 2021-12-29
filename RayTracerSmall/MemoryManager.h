#ifndef _MEMORY_MANAGER_H_
#define _MEMORY_MANAGER_H_
#include "MemoryPool.h"

enum class MemPoolType
{
	GEN_POOL = 0,
	SCENES_POOL = 1,
	RENDERER_POOL = 2
};

class MemManager
{
public:

	static MemManager* memPoolSelf;

	MemoryPool* genMemPool;
	MemoryPool* sceneMemPool;
	MemoryPool* rendererMemoryPool;

	void DeleteVariableInMemPool(void* MPmemory, MemPoolType MPtype);
	void* SaveVariableToMemPool(size_t MPsize, MemPoolType MPtype);
	
	void operator delete(void* MPmem);
	void* operator new(size_t MPsize);

	MemManager();
	~MemManager();

};

class MemoryManagerRef
{

public:
	static MemManager* memoryManager;

};

#endif