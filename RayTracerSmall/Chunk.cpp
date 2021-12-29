#include "Chunk.h"

Chunk::Chunk(Chunk* nextChunk, Chunk* previousChunk, size_t sizeMemoryToSave, bool available) : LNextChunk(nextChunk), LpreviousChunk(previousChunk), SizeOfUserMem(sizeMemoryToSave), Mfree(available)
{
	//  n/a
}

Chunk::~Chunk()
{
	LpreviousChunk = nullptr;
	LNextChunk = nullptr;
	
	Mfree = NULL;
	SizeOfUserMem = NULL;
}

Chunk* Chunk::FindOldChunk(size_t ai_sizeOfVar)
{
	if (ai_sizeOfVar == SizeOfUserMem && Mfree == true)
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
	if (VarSize == SizeOfUserMem && Mfree == true)
	{
		return this;
	}
	else if (LNextChunk == nullptr)
	{
		LNextChunk = (Chunk*)((char*)this + (sizeof(Chunk) + SizeOfUserMem));
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
	SizeOfUserMem = VarSize;
	Mfree = false;

	return (((char*)SaveLocation) + sizeof(Chunk));
}



