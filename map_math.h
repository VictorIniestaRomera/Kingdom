#pragma once

#include "math.h"

#include "point2.h"

namespace util {
	class MapMath {
	public:
		inline static int calc_distance(const util::Point2& p1, const util::Point2& p2) noexcept {
			return util::Math::square_root(util::Math::pow(p1.x - p2.x, 2) + util::Math::pow(p1.y - p2.y, 2));
		}
	};
}