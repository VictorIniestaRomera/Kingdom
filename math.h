#ifndef K_MATH_H
#define K_MATH_H

namespace util {
	class Math {
	public:
		inline static double pow(const double x, const int to) noexcept {
			double res = x;

			for (int i = 1; i != to; i++) {
				res *= x;
			}

			return res;
		}

		inline static double square_root(const double x) noexcept {
			double res = x / 2;

			for (int i = 10; i != 0; i--) {
				res = 0.5f * (res + x / res);
			}

			return res;
		}

		inline static double absolute(double x) noexcept {
			if (x < 0) x *= -1;

			return x;
		}
	};
}
#endif