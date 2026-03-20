#ifndef VILLAGE_H
#define VILLAGE_H

#include "chunk.h"

class Village : public Chunk {
	bool hasTeam = false;
	
	Team* team;

public:
	Village() : team(Team::get_singleton()) {
		type = ChunkWritings::VILLAGE;
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