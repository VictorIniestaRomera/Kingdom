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

	MapReader::get_singleton()->set_path("./papers/map1.txt");

	util::Core<char> getMap = MapReader::get_singleton()->read();
	int count = 0;
	
	for (int i = 0; i != Y; i++) {
		map.push_back(new util::Core<Chunk*>);

		for (int j = 0; j != X; j++) {
			try {
				if (getMap.at(count) == MapWritings::PLAIN) map.at(i)->push_back(new Plain());
				else if (getMap.at(count) == MapWritings::RIVER) map.at(i)->push_back(new River());
				else if (getMap.at(count) == MapWritings::MOUNTAIN) map.at(i)->push_back(new Mountain());
				else if (getMap.at(count) == MapWritings::CASTLE) map.at(i)->push_back(new Castle());
				else if (getMap.at(count) == MapWritings::VILLAGE) map.at(i)->push_back(new Village());
				else if (getMap.at(count) == MapWritings::FOREST) map.at(i)->push_back(new Forest());
				else if (getMap.at(count) == MapWritings::CONTROL_POINT) map.at(i)->push_back(new ControlPoint());
				else throw(new MapReaderException(2));
			}
			catch (const MapReaderException* e) {
				std::cerr << "Chunk pos " << count << ": " << e->what() << std::endl;

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
		std::cerr << "Error; Map not constructed!\n";

		return nullptr;
	}

	return manager;
}

void Map::draw_map() noexcept {
	system("cls");

	for (int i = 0; i != Y; i++) {
		for (int j = 0; j != X; j++) {
			const Chunk* c = map.at(i)->at(j);

			std::cout << " " << c->get_color() << c->get_drawing();
		}

		std::cout << ColorWritings::WHITE << " *" << std::endl;
	}

	for (int i = 0; i != X; i++) {
		std::cout << ColorWritings::WHITE << " *";
	}

	std::cout << ColorWritings::WHITE << " *" << std::endl;
}