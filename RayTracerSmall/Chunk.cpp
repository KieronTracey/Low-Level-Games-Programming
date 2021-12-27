#include "Chunk.h"

Chunk::Chunk(Chunk* ap_nextChunk, Chunk* ap_previousChunk, size_t ai_memToSaveSize, bool ab_free) :
	mp_nextChunkLocation(ap_nextChunk), mp_previousChunk(ap_previousChunk), mi_userMemSize(ai_memToSaveSize), mb_free(ab_free)
{
}

Chunk::~Chunk()
{
	mp_nextChunkLocation = nullptr;
	mp_previousChunk = nullptr;
	mi_userMemSize = NULL;
	mb_free = NULL;
}

void* Chunk::Write(void* ap_locationToSave, size_t sizeOfVar)
{
	//- Offset the pointer by the size of the chunk class -//
	mi_userMemSize = sizeOfVar;
	mb_free = false;
	return (((char*)ap_locationToSave) + sizeof(Chunk));
}

Chunk* Chunk::GetNextAvalableChunkAdress(size_t ai_sizeOfVar)
{
	if (ai_sizeOfVar == mi_userMemSize && mb_free == true)
	{
		return this;
	}
	else if (mp_nextChunkLocation == nullptr)
	{
		mp_nextChunkLocation = (Chunk*)((char*)this + (sizeof(Chunk) + mi_userMemSize));
		mp_nextChunkLocation->mb_free = false;
		return mp_nextChunkLocation;
	}
	else
	{
		return mp_nextChunkLocation->GetNextAvalableChunkAdress(ai_sizeOfVar);
	}

	return nullptr;
}

Chunk* Chunk::GetPreviousChunkAdress(size_t ai_sizeOfVar)
{
	if (ai_sizeOfVar == mi_userMemSize && mb_free == true)
	{
		return mp_previousChunk;
	}
	else if (mp_nextChunkLocation == nullptr)
	{
		return this;
	}
	else
	{
		return mp_nextChunkLocation->GetPreviousChunkAdress(ai_sizeOfVar);
	}
}
