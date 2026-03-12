#pragma once

#include "player.h"

class ThirdPlayer : public Player {
	const util::Core<util::Core<Chunk*>*>* map;

public:
	ThirdPlayer(const util::Core<util::Core<Chunk*>*>* m) : map(m) {
		set_team("third", 3);

		set_castle();
		set_control_points();
	}

	void set_castle() noexcept override {
		const int Y = map->size();
		const int X = map->at(0)->size();

		for (int i = 0; i != Y; i++) {
			for (int j = 0; j != X; j++) {
				Chunk* c = map->at(i)->at(j);

				if (c->get_drawing() == MapWritings::CASTLE && !c->has_team()) {
					teamMap.push_back(new util::Point2(i, j));

					c->change_team(this);

					return;
				}
			}
		}
	}

	void set_control_points() noexcept override {
		const int Y = map->size();
		const int X = map->at(0)->size();

		util::Point2* castlePos = teamMap.at(0);

		for (int i = 0; i != Y; i++) {
			for (int j = 0; j != X; j++) {
				Chunk* c = map->at(i)->at(j);

				if ((c->get_drawing() == MapWritings::CONTROL_POINT || c->get_drawing() == MapWritings::VILLAGE) && !c->has_team()) {
					if (util::MapMath::calc_distance(*castlePos, util::Point2(i, j)) <= 20) {
						teamMap.push_back(new util::Point2(i, j));

						c->change_team(this);
					}
				}
			}
		}
	}
};