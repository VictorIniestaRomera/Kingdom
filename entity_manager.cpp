#include "entity_manager.h"

#include "log_writer.h"

#include "entity_manager_exception.h"

#include "woods_man.h"
#include "builder.h"

EntityManager* EntityManager::manager = nullptr;

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {}

EntityManager* EntityManager::get_singleton() {
	if (!manager) manager = new EntityManager();
	
	return manager;
}

void EntityManager::add_entity(const EntityWritings::Drawing& type, const char* name, const util::Point2& pos) {
	try {
		for (int i = 0; i < entityList.size(); i++) {
			if (pos == entityList.at(i)->get_position()) throw(new EntityManagerException(1));
		}

		Entity* entity = nullptr;

		if (type == EntityWritings::WOODS_MAN) entity = new WoodsMan(name, pos);
		else if (type == EntityWritings::BUILDER) entity = new Builder(name, pos);
		else throw(new EntityManagerException(2));

		entityList.push_back(entity);
	}
	catch (const EntityManagerException* e) {
		LogWriter::log(e->what());

		delete e;
	}
}

void EntityManager::remove_entity(util::Point2 p) {
	try {
		int pos = get_list_pos_at(p);

		if (pos == -1) throw(new EntityManagerException(1));

		entityList.remove(pos);
	}
	catch (const EntityManagerException* e) {
		LogWriter::log(e->what());

		delete e;
	}
}

const int EntityManager::get_list_pos_at(const util::Point2& pos) const noexcept {
	for (int i = 0; i < entityList.size(); i++) {
		if (entityList.at(i)->get_position() == pos) return i;
	}

	return -1;
}

const char EntityManager::entity_writing_at(const util::Point2& p) const {
	try {
		int pos = get_list_pos_at(p);

		if (pos == -1) throw(new EntityManagerException(0));

		return entityList.at(get_list_pos_at(p))->get_writing();
	}
	catch (const EntityManagerException* e) {
		LogWriter::log(e->what());

		delete e;

		return EntityWritings::ENTITY_ERROR;
	}
}

const char* EntityManager::entity_color_at(const util::Point2& p) const {
	try {
		int pos = get_list_pos_at(p);

		if (pos == -1) throw(new EntityManagerException(0));

		return entityList.at(get_list_pos_at(p))->get_color();
	}
	catch (const EntityManagerException* e) {
		LogWriter::log(e->what());

		delete e;

		return ColorWritings::RED;
	}
}

void EntityManager::update_entities(const util::Core<util::Core<Chunk*>*>* map) noexcept {
	for (int i = 0; i < entityList.size(); i++) {
		entityList.at(i)->update(map);
	}
}