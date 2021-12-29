#include "Chunk.h"



Chunk* Chunk::FindOldChunk(size_t ai_sizeOfVar)
{
	if (ai_sizeOfVar == SizeOfAvailableMemory && Mfree == true)
	{
		return LpreviousChunk;
	}
	else if (LNextChunk == nullptr)
	{
		return this;
	}
	else
	{
		return LNextChunk->FindOldChunk(ai_sizeOfVar);
	}
}

Chunk* Chunk::FindNewChunk(size_t VarSize)
{
	if (VarSize == SizeOfAvailableMemory && Mfree == true)
	{
		return this;
	}
	else if (LNextChunk == nullptr)
	{
		LNextChunk = (Chunk*)((char*)this + (sizeof(Chunk) + SizeOfAvailableMemory));
		LNextChunk->Mfree = false;
		return LNextChunk;
	}
	else
	{
		return LNextChunk->FindNewChunk(VarSize);
	}

	return nullptr;
}

// change pointer by chunk size
void* Chunk::ChangePointer(void* SaveLocation, size_t VarSize)
{
	SizeOfAvailableMemory = VarSize;
	Mfree = false;

	return (((char*)SaveLocation) + sizeof(Chunk));
}

Chunk::Chunk(Chunk* nextChunk, Chunk* previousChunk, size_t sizeMemoryToSave, bool available) : LNextChunk(nextChunk), LpreviousChunk(previousChunk), SizeOfAvailableMemory(sizeMemoryToSave), Mfree(available)
{
	//  n/a
}

Chunk::~Chunk()
{
	LpreviousChunk = nullptr;
	LNextChunk = nullptr;

	Mfree = NULL;
	SizeOfAvailableMemory = NULL;
}



