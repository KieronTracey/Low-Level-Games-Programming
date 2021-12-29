#include "MemoryPool.h"
#include "VecTemplate.h"`

MemoryPool::MemoryPool(size_t ai_sizeOfPoolInBytes) :
	mp_memPool((unsigned char*)malloc(ai_sizeOfPoolInBytes)), mi_maxBytes(ai_sizeOfPoolInBytes), mi_usedBytes(0), mi_allocatedBytes(0),
	mp_initalChunk((Chunk*)mp_memPool), mi_sizeOfChunk(sizeof(Chunk))
{
}

MemoryPool::~MemoryPool()
{
	delete mp_memPool;
	mi_sizeOfChunk = NULL;
	mi_usedBytes = NULL;
	mi_allocatedBytes = NULL;
	mi_maxBytes = NULL;
	mp_initalChunk = nullptr;
}

void* MemoryPool::Alloc(size_t ai_varSize)
{
	if (ai_varSize < mi_maxBytes - mi_usedBytes)
	{
		//- declare the var//
		Chunk* lp_previousChunkLocation;
		Chunk* lp_chunkSavePointer;

		//- if first time around calcuate where to place first chunk -//
		if (mi_allocatedBytes == 0)
		{
			//- Set Pointer to the start of the pool and null previous -//
			lp_chunkSavePointer = mp_initalChunk;
			lp_chunkSavePointer->Mfree = false;
			lp_previousChunkLocation = nullptr;
		}
		else
		{
			lp_previousChunkLocation = mp_initalChunk->FindOldChunk(ai_varSize);
			lp_chunkSavePointer = mp_initalChunk->FindNewChunk(ai_varSize);
		}

		//- Set Up Memory Chunk To Store variable information -//
		if (lp_chunkSavePointer->Mfree == false)
		{
			Chunk l_chunk = Chunk(nullptr, lp_previousChunkLocation, ai_varSize, true);
			memcpy(lp_chunkSavePointer, &l_chunk, mi_sizeOfChunk);
			mi_allocatedBytes += mi_sizeOfChunk + ai_varSize;
		}

		mi_usedBytes += mi_sizeOfChunk + ai_varSize;

		//- return the adress of the data calculated in Write Function -//
		return lp_chunkSavePointer->ChangePointer(lp_chunkSavePointer, ai_varSize);
	}

	cout << "Not Enough Memory Required Space is: " << ai_varSize << " and only: " << mi_maxBytes - mi_allocatedBytes << " left\n";

	return nullptr;
}


void MemoryPool::Free(void* p)
{
	if (p != nullptr)
	{
		Chunk* lp_chunk = (Chunk*)((char*)p - mi_sizeOfChunk);
		if (lp_chunk->Mfree == false)
		{
			lp_chunk->Mfree = true;
			mi_usedBytes -= lp_chunk->SizeOfUserMem + mi_sizeOfChunk;
		}
	}
}

int MemoryPool::AmountOfBytesUsed()
{
	return mi_allocatedBytes;
}

void* MemoryPool::operator new(size_t size)
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

void MemoryPool::operator delete(void* pMem)
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
