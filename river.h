#pragma once

#include "chunk.h"

class River : public Chunk {
public:
	River() {
		type = MapWritings::RIVER;
		modifyMovement = -1.0f;
		color = ColorWritings::BLUE;
	}
};