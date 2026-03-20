#ifndef MAP_WRITINGS_H
#define MAP_WRITINGS_H

#include "color_writings.h"

struct ChunkWritings {
	enum Drawing {
		CHUNK_ERROR = 'E',
		PLAIN = '-',
		RIVER = '/',
		MOUNTAIN = '|',
		CASTLE = 'W',
		CONTROL_POINT = 'M',
		VILLAGE = 'N',
		FOREST = 'T'
	};

protected:
	Drawing type;
	const char* color;
	int modifyMovement;
	bool isVisible = true;
};

struct EntityWritings {
	enum Drawing {
		ENTITY_ERROR = 'E',
		BUILDER = '$',
		WOODS_MAN = 'P'
	};

protected:
	Drawing type;
	int speed;
	const char* color;
};
#endif