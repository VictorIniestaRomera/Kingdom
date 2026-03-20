#ifndef RIVER_H
#define RIVER_H

#include "chunk.h"

class River : public Chunk {
public:
	River() {
		type = ChunkWritings::RIVER;
		modifyMovement = -1;
		color = ColorWritings::BLUE;
	}
};
#endif