#ifndef ENTITY_MANAGER_EXCEPTION_H
#define ENTITY_MANAGER_EXCEPTION_H

#include "exception.h"

#include "core.h"

class EntityManagerException : public Exception {
	const int code;

public:
	EntityManagerException(const int code) : code(code) {}

	~EntityManagerException() {}

	inline const char* what() const noexcept override {
		const char* txt;

		if (code == 0) txt = "Entity not found!";
		else if (code == 1) txt = "Entity spawn position not valid!";
		else if (code == 2) txt = "Entity not valid!";
		else txt = "Unknown entity exception!";

		return txt;
	}
};

#endif