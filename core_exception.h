#pragma once

#include "exception.h"

class CoreException : public Exception {
	const int code;

public:
	CoreException(const int code) : code(code) {}

	~CoreException() {};

	inline const char* what() const noexcept override {
		const char* txt;

		if (code == 1) txt = "Index out of bounds!";
		else if (code == 2) txt = "Max size has ben locked!";
		else txt = "Unknown core exception!";

		return txt;
	}
};