#include "MemoryManager.h"

MemoryManager::MemoryManager()
{
	mp_genralMemoryPool = new MemoryPool(1000000000);
	mp_sceneMemoryPool = new MemoryPool(50000000);
	mp_rendererMemoryPool = new MemoryPool(50000000);
}

MemoryManager::~MemoryManager()
{

}

void* MemoryManager::SaveVarToMemoryPool(size_t ai_size, PoolType a_type)
{
	switch (a_type)
	{
	case PoolType::GENRAL_POOL:
		return mp_genralMemoryPool->Alloc(ai_size);
		break;

	case PoolType::SCENE_POOL:
		return mp_sceneMemoryPool->Alloc(ai_size);
		break;

	case PoolType::RENDER_POOL:
		return mp_rendererMemoryPool->Alloc(ai_size);
		break;

	default:
		return nullptr;
		break;
	}
}

void MemoryManager::DeleteVarToMemoryPool(void* ap_memory, PoolType a_type)
{
	switch (a_type)
	{
	case PoolType::GENRAL_POOL:
		mp_genralMemoryPool->Free(ap_memory);
		break;

	case PoolType::SCENE_POOL:
		mp_sceneMemoryPool->Free(ap_memory);
		break;

	case PoolType::RENDER_POOL:
		mp_rendererMemoryPool->Free(ap_memory);
		break;
	}
}

void* MemoryManager::operator new(size_t size)
{
	size_t nRequestedBytes = size + sizeof(MemoryHeader) + sizeof(MemoryFooter);
	char* pMem = (char*)malloc(nRequestedBytes);
	MemoryHeader* pHeader = (MemoryHeader*)pMem;

	pHeader->mi_sizeOfVar = size;
	pHeader->mi_errorCheck = 0xDEADC0DE;

	void* pFooterAddr = pMem + sizeof(MemoryHeader) + size;
	MemoryFooter* pFooter = (MemoryFooter*)pFooterAddr;

	void* pStartMemBlock = pMem + sizeof(MemoryHeader);
	return pStartMemBlock;
}

void MemoryManager::operator delete(void* pMem)
{
	MemoryHeader* pHeader = (MemoryHeader*)((char*)pMem - sizeof(MemoryHeader));
	if (pHeader->mi_errorCheck != 0xDEADC0DE)
	{
		cout << "ERROR CHECK MEMORY OVER RUN \n";
		cout << "MEMORY WILL NOT BE DELETED PLEASE FIX AND TRY AGAIN \n";
	}
	else
	{
		MemoryFooter* pFooter = (MemoryFooter*)((char*)pMem + pHeader->mi_sizeOfVar);
		free(pHeader);
	}
}
