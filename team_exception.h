#ifndef TEAM_ERROR_H
#define TEAM_ERROR_H

#include "exception.h"

class TeamException : public Exception {
	int code;

public:
	TeamException(int code) : code(code) {}

	~TeamException() {}

	inline const char* what() const noexcept override {
		const char* txt;

		if (code == 1) txt = "Team not found!";
		else txt = "Unknown team error!";

		return txt;
	}
};

#endif