#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include "chunk.h"

class Mountain : public Chunk {
public:
	Mountain() {
		type = ChunkWritings::MOUNTAIN;
		modifyMovement = -2;
		color = ColorWritings::GRAY;
	}
};
#endif