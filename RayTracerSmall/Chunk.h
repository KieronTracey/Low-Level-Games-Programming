#ifndef _CHUNK_H_
#define _CHUNK_H_
#include <cstring>

class Chunk
{
public:
	
	Chunk(Chunk* ap_nextChunk, Chunk* ap_previousChunk, size_t ai_memToSaveSize, bool ab_free);
	~Chunk();

	void* Write(void* ap_locationToSave, size_t sizeOfVar);
	Chunk* GetNextAvalableChunkAdress(size_t ai_sizeOfVar);
	Chunk* GetPreviousChunkAdress(size_t ai_sizeOfVar);

	Chunk* mp_nextChunkLocation;
	Chunk* mp_previousChunk;
	size_t mi_userMemSize;
	bool mb_free;
};

#endif
