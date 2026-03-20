#ifndef ERROR_CHUNK_H
#define ERROR_CHUNK_H

#include "chunk.h"

class ErrorChunk : public Chunk {
public:
	ErrorChunk() {
		type = ChunkWritings::CHUNK_ERROR;
		modifyMovement = 0;
		color = ColorWritings::RED;
	}
};
#endif