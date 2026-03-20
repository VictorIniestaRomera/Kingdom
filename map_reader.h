#ifndef MAP_READER_H
#define MAP_READER_H

#include <fstream>

#include "log_writer.h"

#include "map_reader_exception.h"
#include "core.h"

class MapReader {
	static MapReader* manager;

	const char* path;

public:
	static MapReader* get_singleton() {
		if (!manager) manager = new MapReader();

		return manager;
	}

	inline void set_path(const char* p) {
		path = p;

		std::string txt = "Map loaded path: ";
		txt += p;

		LogWriter::log(txt.c_str());
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
			LogWriter::log(e->what());

			delete e;

			return list;
		}

		return list;
	}
};

MapReader* MapReader::manager = nullptr;

#endif