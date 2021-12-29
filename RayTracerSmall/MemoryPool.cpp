#include "VecTemplate.h"`
#include "MemoryPool.h"

int MemoryPool::AmountOfMemoryUsed()
{
	return Hallocatedmemory;
}

void MemoryPool::FreeMemory(void* var)
{
	if (var != nullptr)
	{
		Chunk* MPchunk = (Chunk*)((char*)var - HsizeOfChunk);
		if (MPchunk->Mfree == false)
		{
			MPchunk->Mfree = true;
			HusedBytes -= MPchunk->SizeOfAvailableMemory + HsizeOfChunk;
		}
	}
}

void* MemoryPool::operator new(size_t size)
{
	size_t neededMemory = size + sizeof(MemoryHeader) + sizeof(MemoryFooter);
	char* MPmemory = (char*)malloc(neededMemory);
	MemoryHeader* pHeader = (MemoryHeader*)MPmemory;

	pHeader->MPsizeOfVariable = size;
	pHeader->MPerrorCheck = 0xDEADC0DE;

	void* MPfooterAdit = MPmemory + sizeof(MemoryHeader) + size;
	MemoryFooter* MPfooter = (MemoryFooter*)MPfooterAdit;

	void* MPStartMemoryChunk = MPmemory + sizeof(MemoryHeader);
	return MPStartMemoryChunk;
}

void MemoryPool::operator delete(void* MPmemory)
{
	MemoryHeader* MPheader = (MemoryHeader*)((char*)MPmemory - sizeof(MemoryHeader));
	if (MPheader->MPerrorCheck != 0xDEADC0DE)
	{
		std::cout << "ERROR: over memory limit \n";
	}
	else
	{
		MemoryFooter* MPfooter = (MemoryFooter*)((char*)MPmemory + MPheader->MPsizeOfVariable);
		free(MPheader);
	}
}

void* MemoryPool::Allocate(size_t variableSize)
{
	if (variableSize < HmaxMem - HusedBytes)
	{
		// firstly declare variable
		Chunk* MPlocOfLastChunk;
		Chunk* MPsaveChunkPointer;

		// allocate chunk if none exist, else continue from old chunk
		if (Hallocatedmemory == 0)
		{
			MPsaveChunkPointer = FirstChunk;
			MPsaveChunkPointer->Mfree = false;
			MPlocOfLastChunk = nullptr;
		}
		else
		{
			MPlocOfLastChunk = FirstChunk->FindOldChunk(variableSize);
			MPsaveChunkPointer = FirstChunk->FindNewChunk(variableSize);
		}

		// setup chunk to store variables
		if (MPsaveChunkPointer->Mfree == false)
		{
			Chunk MPchunk = Chunk(nullptr, MPlocOfLastChunk, variableSize, true);
			memcpy(MPsaveChunkPointer, &MPchunk, HsizeOfChunk);
			Hallocatedmemory += HsizeOfChunk + variableSize;
		}

		HusedBytes += HsizeOfChunk + variableSize;

		return MPsaveChunkPointer->ChangePointer(MPsaveChunkPointer, variableSize);
	}

	std::cout << "OUT OF MEMORY!";
	std::cout << "Need: " << variableSize << " to run and this machine only has: " << HmaxMem - Hallocatedmemory << " remaining";


	return nullptr;
}



MemoryPool::MemoryPool(size_t poolsize) : HmemPool((unsigned char*)malloc(poolsize)), HmaxMem(poolsize), HusedBytes(0), Hallocatedmemory(0), FirstChunk((Chunk*)HmemPool), HsizeOfChunk(sizeof(Chunk))
{
	// empty
}

//free memory
MemoryPool::~MemoryPool()
{
	delete HmemPool;

	Hallocatedmemory = NULL;
	HmaxMem = NULL;
	HsizeOfChunk = NULL;
	HusedBytes = NULL;

	FirstChunk = nullptr;
}
