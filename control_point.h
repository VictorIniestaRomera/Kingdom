#pragma once

#include "chunk.h"

class ControlPoint : public Chunk {
	Player* team;
	bool hasTeam = false;

public:
	ControlPoint() : team(nullptr) {
		type = MapWritings::CONTROL_POINT;
		modifyMovement = 0.0f;
		color = ColorWritings::WHITE;
	}

	void change_team(Player* p) noexcept override {
		team = p;

		color = p->get_team_color();

		hasTeam = true;
	}

	bool has_team() noexcept override {
		return hasTeam;
	}
};