#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "entity.h"

#include "core.h"
#include "point2.h"

class EntityManager {
	static EntityManager* manager;

	util::Core<Entity*> entityList;

	const int get_list_pos_at(const util::Point2& pos) const noexcept;

public:
	EntityManager();
	~EntityManager();

	static EntityManager* get_singleton();

	void add_entity(const EntityWritings::Drawing& type, const char* name, const util::Point2& pos);

	void remove_entity(util::Point2 p);

	const char entity_writing_at(const util::Point2& p) const;

	const char* entity_color_at(const util::Point2& p) const;

	void update_entities(const util::Core<util::Core<Chunk*>*>* map) noexcept;
};
#endif