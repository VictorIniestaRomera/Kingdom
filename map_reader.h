#pragma once

#include <fstream>
#include <iostream>

#include "map_reader_exception.h"
#include "core.h"

class MapReader {
	static MapReader* manager;

	std::string path;

public:
	static MapReader* get_singleton() {
		if (!manager) manager = new MapReader();

		return manager;
	}

	inline void set_path(std::string p) {
		path = p;
	}

	inline util::Core<char> read() {
		util::Core<char> list;

		try {
			std::ifstream paper(path);

			if (!paper.is_open()) throw(new MapReaderException(1));

			char get;

			while (paper >> get) {
				list.push_back(get);
			}

			list.lock();

			paper.close();
		}
		catch (const MapReaderException* e) {
			std::cerr << e->what() << std::endl;

			delete e;

			return list;
		}

		return list;
	}
};

MapReader* MapReader::manager = nullptr;