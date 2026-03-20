#ifndef BUILDER_H
#define BUILDER_H

#include "entity.h"

class Builder : public Entity {
	Team* team;

public:
	Builder(const char* name, util::Point2 p) : team(Team::get_singleton()) {
		type = EntityWritings::BUILDER;
		speed = 1;
		pos = p;

		color = team->get_team_color("one");
	}
};
#endif