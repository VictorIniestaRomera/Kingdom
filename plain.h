#pragma once

#include "chunk.h"

class Plain : public Chunk {
public:
	Plain() {
		type = MapWritings::PLAIN;
		modifyMovement = 0.0f;
		color = ColorWritings::BLACK;
	}
};