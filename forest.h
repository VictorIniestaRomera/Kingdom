#ifndef FOREST_H
#define FOREST_H

#include "chunk.h"

class Forest : public Chunk {
public:
	Forest() {
		type = ChunkWritings::FOREST;
		modifyMovement = -1;
		color = ColorWritings::GREEN;
	}
};
#endif