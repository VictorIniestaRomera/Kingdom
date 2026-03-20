#include "map_manager.h"

#include "map_reader.h"
#include "map_writings.h"
#include "color_writings.h"

#include "error_chunk.h"
#include "plain.h"
#include "river.h"
#include "mountain.h"
#include "castle.h"
#include "control_point.h"
#include "village.h"
#include "forest.h"

Map* Map::manager = nullptr;

Map::Map(const int y, const int x) : Y(y), X(x) {
	manager = this;
	entityManager = EntityManager::get_singleton();

	MapReader::get_singleton()->set_path("./papers/map1.txt");

	util::Core<char> getMap = MapReader::get_singleton()->read();
	int count = 0;
	
	for (int i = 0; i != Y; i++) {
		map.push_back(new util::Core<Chunk*>);

		for (int j = 0; j != X; j++) {
			try {
				if (getMap.at(count) == ChunkWritings::PLAIN) map.at(i)->push_back(new Plain());
				else if (getMap.at(count) == ChunkWritings::RIVER) map.at(i)->push_back(new River());
				else if (getMap.at(count) == ChunkWritings::MOUNTAIN) map.at(i)->push_back(new Mountain());
				else if (getMap.at(count) == ChunkWritings::CASTLE) map.at(i)->push_back(new Castle());
				else if (getMap.at(count) == ChunkWritings::VILLAGE) map.at(i)->push_back(new Village());
				else if (getMap.at(count) == ChunkWritings::FOREST) map.at(i)->push_back(new Forest());
				else if (getMap.at(count) == ChunkWritings::CONTROL_POINT) map.at(i)->push_back(new ControlPoint());
				else throw(new MapReaderException(2));
			}
			catch (MapReaderException* e) {
				e->what();

				delete e;

				map.at(i)->push_back(new ErrorChunk());
			}

			count++;
		}

		map.at(i)->lock(X);
	}

	map.lock(Y);
}

Map::~Map() {
	for (int i = 0; i != Y; i++) {
		delete map.at(i);
	}
}

Map* Map::get_singleton() {
	if (!manager) {
		LogWriter::log("Error; Map not constructed!\n");

		return nullptr;
	}

	return manager;
}

void Map::draw_map() noexcept {
	system("cls");

	char y, y1;
	char x, x1;

	y = x = '0';
	y1 = x1 = 'A';

	for (int i = 0; i != Y; i++) {
		for (int j = 0; j != X; j++) {
			const Chunk* c = map.at(i)->at(j);

			if (c->is_visible()) std::cout << " " << c->get_color() << c->get_drawing();
			else std::cout << " " << entityManager->entity_color_at(util::Point2(i, j)) << entityManager->entity_writing_at(util::Point2(i, j));
		}

		std::cout << ColorWritings::WHITE << " * " << y << y1 << std::endl;

		y++;

		if (y == ':') {
			y = '0';
			y1++;
		}
	}

	for (int i = 0; i != X; i++) {
		std::cout << ColorWritings::WHITE << " *";
	}

	std::cout << std::endl;

	for (int i = 0; i != X; i++) {
		std::cout << ColorWritings::WHITE << " " << x;

		x++;

		if (x == ':') x = '0';
	}

	std::cout << std::endl;

	for (int i = 0; i != X; i++) {
		std::cout << ColorWritings::WHITE << " " << x1;

		x++;

		if (x == ':') {
			x = '0';
			x1++;
		}
	}

	std::cout << std::endl;
}

void Map::add_entity(const EntityWritings::Drawing& type, const char* name, const util::Point2& pos) {
	const Chunk* c = map.at(pos.y)->at(pos.x);
	ChunkWritings::Drawing spawnPlace;

	if (type == EntityWritings::BUILDER || type == EntityWritings::WOODS_MAN) spawnPlace = ChunkWritings::VILLAGE;
	else spawnPlace = ChunkWritings::CHUNK_ERROR;

	if (c->get_drawing() == spawnPlace) entityManager->add_entity(type, name, pos);
	else LogWriter::log("Entity placement invalid!");
}