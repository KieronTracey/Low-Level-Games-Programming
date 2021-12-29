#ifndef _CHUNK_H_
#define _CHUNK_H_
#include <cstring>

class Chunk
{
public:
	size_t SizeOfUserMem;
	bool Mfree;

	Chunk(Chunk* nextChunk, Chunk* previousChunk, size_t sizeMemoryToSave, bool available);
	~Chunk();

	Chunk* FindOldChunk(size_t VarSize);
	Chunk* FindNewChunk(size_t VarSize);
	
	Chunk* LpreviousChunk;
	Chunk* LNextChunk;

	void* ChangePointer(void* SaveLocation, size_t VarSize);
	
};

#endif
