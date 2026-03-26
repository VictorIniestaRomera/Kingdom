#ifndef PLAYER_H
#define PLAYER_H

#include "map_math.h"
#include "map_writings.h"

#include "team_manager.h"

#include "chunk.h"

class Player {
	bool hasFinished = false;

	Team* team;

	const util::Core<util::Core<Chunk*>*>* map;

public:
	Player(const char* teamName, const util::Core<util::Core<Chunk*>*>* m);

	~Player();

	void set_castle() noexcept;

	void set_control_points() noexcept;

	inline const bool finished() const {
		return hasFinished;
	}

	inline void switch_finished() {
		if (hasFinished) hasFinished = false;
		else hasFinished = true;
	}
};
#endif