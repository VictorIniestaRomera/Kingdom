#pragma once

#include "chunk.h"

class Forest : public Chunk {
public:
	Forest() {
		type = MapWritings::FOREST;
		modifyMovement = -0.5f;
		color = ColorWritings::GREEN;
	}
};