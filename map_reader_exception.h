#pragma once

#include "exception.h"

class MapReaderException : public Exception {
	const int code;

public:
	MapReaderException(const int code) : code(code) {}

	~MapReaderException() {};

	inline const char* what() const noexcept override {
		const char* txt;

		if (code == 1) txt = "Paper not found!";
		if (code == 2) txt = "Chunk not recognized!";
		else txt = "Unknown map reader exception!";

		return txt;
	}
};