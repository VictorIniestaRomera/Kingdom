#include "player.h"

Player::Player(const char* teamName, const util::Core<util::Core<Chunk*>*>* m) : map(m), team(Team::get_singleton()) {
	team->add_team(teamName);

	set_castle();
	set_control_points();
}

Player::~Player() {}

void Player::set_castle() noexcept {
	const int Y = map->size();
	const int X = map->at(0)->size();

	TeamData* data = team->get_data(team->get_name());

	for (int i = 0; i != Y; i++) {
		for (int j = 0; j != X; j++) {
			Chunk* c = map->at(i)->at(j);

			if (c->get_drawing() == ChunkWritings::CASTLE && !c->has_team()) {
				data->teamMap.push_back(new util::Point2(i, j));

				c->set_team(data->teamName);

				return;
			}
		}
	}
}

void Player::set_control_points() noexcept {
	const int Y = map->size();
	const int X = map->at(0)->size();

	TeamData* data = team->get_data(team->get_name());

	util::Point2* castlePos = data->teamMap.at(0);

	for (int i = 0; i != Y; i++) {
		for (int j = 0; j != X; j++) {
			Chunk* c = map->at(i)->at(j);

			if ((c->get_drawing() == ChunkWritings::CONTROL_POINT || c->get_drawing() == ChunkWritings::VILLAGE) && !c->has_team()) {
				if (util::MapMath::calc_distance(*castlePos, util::Point2(i, j)) <= 20) {
					data->teamMap.push_back(new util::Point2(i, j));

					c->set_team(data->teamName);
				}
			}
		}
	}
}