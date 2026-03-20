#ifndef ENTITY_H
#define ENTITY_H

#include "map_writings.h"

#include "chunk.h"

#include "team_manager.h"

#include "point2.h"
#include "core.h"

class Entity : public EntityWritings {
protected:
	util::Point2 pos;

public:
	virtual ~Entity() = default;

	inline const int get_speed() const noexcept {
		return speed;
	}

	inline const char* get_color() const noexcept {
		return color;
	}

	inline const util::Point2 get_position() const noexcept {
		return util::Point2(pos.y, pos.x);
	}

	inline const char get_writing() const noexcept {
		return type;
	}

	inline void update(const util::Core<util::Core<Chunk*>*>* map) {
		map->at(pos.y)->at(pos.x)->switch_visible();
	}
};
#endif