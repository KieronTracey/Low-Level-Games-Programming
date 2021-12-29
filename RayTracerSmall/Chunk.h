#ifndef _CHUNK_H_
#define _CHUNK_H_
#include <cstring>

class Chunk
{
public:
	
	Chunk* FindOldChunk(size_t VarSize);
	Chunk* FindNewChunk(size_t VarSize);
	
	void* ChangePointer(void* SaveLocation, size_t VarSize);

	Chunk* LpreviousChunk;
	Chunk* LNextChunk;

	Chunk(Chunk* nextChunk, Chunk* previousChunk, size_t sizeMemoryToSave, bool available);
	~Chunk();

	size_t SizeOfAvailableMemory;
	bool Mfree;
};

#endif
