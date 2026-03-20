#ifndef WOODS_MAN_H
#define WOODS_MAN_H

#include "entity.h"

class WoodsMan : public Entity {
	Team* team;

public:
	WoodsMan(const char* name, util::Point2 p) : team(Team::get_singleton()) {
		type = EntityWritings::WOODS_MAN;
		speed = 1;
		pos = p;

		color = team->get_team_color("one");
	}
};
#endif