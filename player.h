#pragma once

#include "team.h"

#include "core.h"
#include "chunk.h"

#include "map_math.h"

class Player : public Team {
public:
	virtual ~Player() = default;

	virtual void set_castle() noexcept {}

	virtual void set_control_points() noexcept {}

	inline const char* get_team_name() const {
		return teamName;
	}

	inline const char* get_team_color() const {
		return teamColor;
	}
};