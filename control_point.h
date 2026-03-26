#ifndef CONTROL_POINT_H
#define CONTROL_POINT_H

#include "chunk.h"

class ControlPoint : public Chunk {
	bool hasTeam = false;
	
	Team* team;

public:
	ControlPoint() : team(Team::get_singleton()) {
		type = ChunkWritings::CONTROL_POINT;
		modifyMovement = 0;
		color = ColorWritings::WHITE;
	}

	ControlPoint(const char* name) : team(Team::get_singleton()) {
		type = ChunkWritings::CONTROL_POINT;
		modifyMovement = 0;

		set_team(name);
	}

	inline void set_team(const char* name) noexcept override {
		color = team->get_color();

		hasTeam = true;
	}

	inline bool has_team() noexcept override {
		return hasTeam;
	}

	inline const char* get_team() const override {
		return team->get_name();
	}
};
#endif