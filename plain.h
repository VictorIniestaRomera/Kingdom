#ifndef PLAIN_H
#define PLAIN_H

#include "chunk.h"

class Plain : public Chunk {
public:
	Plain() {
		type = ChunkWritings::PLAIN;
		modifyMovement = 0;
		color = ColorWritings::BLACK;
	}
};
#endif