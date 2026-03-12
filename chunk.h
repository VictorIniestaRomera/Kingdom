#pragma once

#include "map_writings.h"

#include "player.h"

class Chunk : public MapWritings {
public:
	virtual ~Chunk() = default;

	virtual void change_team(Player* p) noexcept {};

	virtual bool has_team() noexcept {
		return false;
	}

	const inline float get_modified_movement() const noexcept {
		return modifyMovement;
	}

	const inline char get_drawing() const noexcept {
		return (char)type;
	}

	const inline char* get_color() const noexcept {
		return color;
	}
};