#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception {
protected:
	virtual ~Exception() = default;

	inline virtual const char* what() const noexcept = 0;
};
#endif