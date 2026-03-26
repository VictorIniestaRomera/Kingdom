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

	Castle(const char* name) : team(Team::get_singleton()) {
		type = ChunkWritings::CASTLE;
		modifyMovement = 0;
		
		set_team(name);
	}

	inline void set_team(const char* name) override {
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