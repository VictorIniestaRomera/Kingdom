#pragma once

#include "color_writings.h"
#include "map_writings.h"

#include "core.h"
#include "point2.h"

class Team {
protected:
	const char* teamColor;
	const char* teamName;
	util::Core<util::Point2*> teamMap;

public:
	virtual ~Team() = default;

	inline void set_team(const char* name, int num) noexcept {
		teamName = name;

		switch (num) {
		case 1:
			teamColor = ColorWritings::TEAM_1;

			break;

		case 2:
			teamColor = ColorWritings::TEAM_2;

			break;

		case 3:
			teamColor = ColorWritings::TEAM_3;

			break;

		case 4:
			teamColor = ColorWritings::TEAM_4;

			break;

		default:
			std::cerr << "Error";
		}
	}

	inline Team* get_team() {

	}
};