#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>

#include "log_writer.h"

#include "key.h"

class Keyboard {
	static bool pressed;

public:
	~Keyboard() {}

	static const char key_pressed();
};

#endif