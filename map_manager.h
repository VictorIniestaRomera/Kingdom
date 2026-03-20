#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include <iostream>

#include "log_writer.h"

#include "core.h"

#include "chunk.h"

#include "entity_manager.h"

class Map {
	static Map* manager;
	EntityManager* entityManager;

	const int Y, X;

	util::Core<util::Core<Chunk*>*> map;

public:
	Map(const int y, const int x);
	~Map();

	static Map* get_singleton();

	void draw_map() noexcept;
	void add_entity(const EntityWritings::Drawing& type, const char* name, const util::Point2& pos);

	inline const util::Core<util::Core<Chunk*>*>* get_map() const noexcept {
		return &map;
	}
};
#endif