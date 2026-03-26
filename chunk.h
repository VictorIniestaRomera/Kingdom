#ifndef CHUNK_H
#define CHUNK_H

#include "map_writings.h"

#include "team_manager.h"

class Chunk : public ChunkWritings {
public:
	virtual ~Chunk() = default;

	virtual void set_team(const char* name) {}

	virtual bool has_team() noexcept {
		return false;
	}

	virtual const char* get_team() const {
		return "NoTeam";
	}

	inline const int get_modified_movement() const noexcept {
		return modifyMovement;
	}

	inline const char get_drawing() const noexcept {
		return (char)type;
	}

	inline const char* get_color() const noexcept {
		return color;
	}

	inline const bool is_visible() const noexcept {
		return isVisible;
	}

	inline void switch_visible() noexcept {
		if (isVisible) isVisible = false;
		else isVisible = true;
	}
};
#endif