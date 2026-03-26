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

	Village(const char* name) : team(Team::get_singleton()) {
		type = ChunkWritings::VILLAGE;
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