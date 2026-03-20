#ifndef LOG_WRITER_H
#define LOG_WRITER_H

#include <fstream>

#include "point2.h"

class LogWriter {
public:
	static void log(const char* l) {
		static std::ofstream file("./logs/log.txt");

		file << l << "\n" << std::flush;
	}

	static void log(const double l) {
		static std::ofstream file("./logs/log.txt");

		file << l << "\n" << std::flush;
	}

	static void log(const util::Point2& l) {
		static std::ofstream file("./logs/log.txt");

		file << "Y: " << l.y << " X: " << l.x << "\n" << std::flush;
	}

	static void clear() {
		std::ofstream file("./logs/log.txt");

		file.clear();
	}
};

#endif