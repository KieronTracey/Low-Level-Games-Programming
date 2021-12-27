#ifndef _MEMORY_MANAGER_H_
#define _MEMORY_MANAGER_H_

#include <iostream>
#include "MemoryPool.h"

using namespace std;

enum class PoolType
{
	GENRAL_POOL = 0,
	SCENE_POOL,
	RENDER_POOL
};

class MemoryManager
{
public:
	//- Manager Methods -//
	MemoryManager();
	~MemoryManager();

	//- User Accessed/Defined -//

	//- Developer Accessed/Defined -//
	void* SaveVarToMemoryPool(size_t ai_size, PoolType a_type);
	void DeleteVarToMemoryPool(void* ap_memory, PoolType a_type);

	void* operator new(size_t size);
	void operator delete(void* pMem);

	MemoryPool* mp_genralMemoryPool;
	MemoryPool* mp_sceneMemoryPool;
	MemoryPool* mp_rendererMemoryPool;

	static MemoryManager* mp_self;

	//- Templates -//
};

class MemoryManagerRef
{
public:
	static MemoryManager* mp_memoryManager;
};

#endif // !_MEMORY_MANAGER_H_