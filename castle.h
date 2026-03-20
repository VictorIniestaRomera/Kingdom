#ifndef CASTLE_H
#define CASTLE_H

#include "chunk.h"

class Castle : public Chunk {
	bool hasTeam = false;

	Team* team;

public:
	Castle() : team(Team::get_singleton()) {
		type = ChunkWritings::CASTLE;
		modifyMovement = 0;
		color = ColorWritings::WHITE;
	}

	void set_team(const char* name) override {
		color = team->get_team_color("one");

		hasTeam = true;
	}

	bool has_team() noexcept override {
		return hasTeam;
	}
};
#endif