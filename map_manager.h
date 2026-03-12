#pragma once

#include <iostream>

#include "core.h"

#include "chunk.h"

class Map {
	static Map* manager;

	const int Y, X;

	util::Core<util::Core<Chunk*>*> map;

public:
	Map(const int y, const int x);
	~Map();

	static Map* get_singleton();

	void draw_map() noexcept;

	inline const util::Core<util::Core<Chunk*>*>* get_map() const noexcept {
		return &map;
	}
};