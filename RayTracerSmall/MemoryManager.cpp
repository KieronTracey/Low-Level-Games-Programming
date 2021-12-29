#include "MemoryManager.h"


void MemManager::operator delete(void* MPmem)
{
	MemoryHeader* MPheader = (MemoryHeader*)((char*)MPmem - sizeof(MemoryHeader));
	if (MPheader->MPerrorCheck != 0xDEADC0DE)
	{
		std::cout << "OUT OF MEMORY";
	}
	else
	{
		MemoryFooter* MPfooter = (MemoryFooter*)((char*)MPmem + MPheader->MPsizeOfVariable);
		free(MPheader);
	}
}

void* MemManager::operator new(size_t size)
{
	size_t RequiredMemory = size + sizeof(MemoryHeader) + sizeof(MemoryFooter);
	char* MPmem = (char*)malloc(RequiredMemory);
	MemoryHeader* MPheader = (MemoryHeader*)MPmem;

	MPheader->MPsizeOfVariable = size;
	MPheader->MPerrorCheck = 0xDEADC0DE;

	void* MPfooterAdder = MPmem + sizeof(MemoryHeader) + size;
	MemoryFooter* MPfooter = (MemoryFooter*)MPfooterAdder;

	void* MPstartMemoryBlock = MPmem + sizeof(MemoryHeader);
	return MPstartMemoryBlock;
}

void MemManager::DeleteVariableInMemPool(void* MPmemory, MemPoolType dptype)
{
	switch (dptype)
	{
	case MemPoolType::SCENES_POOL:
		sceneMemPool->FreeMemory(MPmemory);
		break;

	case MemPoolType::RENDERER_POOL:
		rendererMemoryPool->FreeMemory(MPmemory);
		break;

	case MemPoolType::GEN_POOL:
		genMemPool->FreeMemory(MPmemory);
		break;
	}
}

void* MemManager::SaveVariableToMemPool(size_t MPsize, MemPoolType MPtype)
{
	switch (MPtype)
	{
	default:
		return nullptr;
		break;

	case MemPoolType::SCENES_POOL:
		return sceneMemPool->Allocate(MPsize);
		break;

	case MemPoolType::RENDERER_POOL:
		return rendererMemoryPool->Allocate(MPsize);
		break;

	case MemPoolType::GEN_POOL:
		return genMemPool->Allocate(MPsize);
		break;
	}
}

MemManager::MemManager()
{
	sceneMemPool = new MemoryPool(70000000);
	rendererMemoryPool = new MemoryPool(70000000);
	genMemPool = new MemoryPool(2000000000);
}

MemManager::~MemManager()
{

}