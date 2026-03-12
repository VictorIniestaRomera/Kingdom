#pragma once

#include "chunk.h"

class Mountain : public Chunk {
public:
	Mountain() {
		type = MapWritings::MOUNTAIN;
		modifyMovement = -1.5f;
		color = ColorWritings::GRAY;
	}
};