#ifndef MAP_MATH_H
#define MAP_MATH_H

#include <iostream>

#include "math.h"

#include "point2.h"

namespace util {
	class MapMath {
	public:
		inline static int calc_distance(const util::Point2& p1, const util::Point2& p2) noexcept {
			return (int)util::Math::square_root(util::Math::pow(p1.x - p2.x, 2) + util::Math::pow(p1.y - p2.y, 2));
		}

		static int calc_pos(const char* pos) noexcept {
			int num = pos[0] - '0';

			char uppPos = std::toupper(pos[1]);
			
			for (char i = 'A'; i != uppPos; i++) {
				num += 10;
			}
			
			return num;
		}
	};
}

#endif