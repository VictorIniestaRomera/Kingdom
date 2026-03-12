#pragma once

#include "chunk.h"

class ErrorChunk : public Chunk {
public:
	ErrorChunk() {
		type = MapWritings::ERROR;
		modifyMovement = 0.0f;
		color = ColorWritings::RED;
	}
};