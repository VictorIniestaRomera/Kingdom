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

	void set_team(const char* name) noexcept override {
		color = team->get_team_color("one");

		hasTeam = true;
	}

	bool has_team() noexcept override {
		return hasTeam;
	}
};
#endif