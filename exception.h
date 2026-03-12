#pragma once

class Exception {
protected:
	virtual ~Exception() = default;

	inline virtual const char* what() const noexcept = 0;
};