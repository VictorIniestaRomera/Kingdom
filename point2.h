#ifndef POINT2_H
#define POINT2_H

namespace util {
	struct Point2 {
		int y;
		int x;

		Point2() : y(0), x(0) {}

		Point2(const int y, const int x) : y(y), x(x) {}
	};
}

inline bool operator==(const util::Point2& p1, const util::Point2& p2) noexcept {
	return ((p1.x == p2.x) && (p1.y == p2.y));
}

inline bool operator!=(const util::Point2& p1, const util::Point2& p2) noexcept {
	return ((p1.x != p2.x) && (p1.y != p2.y));
}

#endif