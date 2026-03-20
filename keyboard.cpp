#include "keyboard.h"

bool Keyboard::pressed = false;

const char Keyboard::key_pressed() {
	if (!pressed) {
		for (char keyCode = Key::A; keyCode != Key::Z; keyCode++) {
			if (GetAsyncKeyState(keyCode) & 0x8000) {
				pressed = true;

				return keyCode;
			}
		}
	}
	else {
		for (char keyCode = Key::A; keyCode != Key::Z; keyCode++) {
			if (GetAsyncKeyState(keyCode) & 0x8000) return keyCode;
		}

		pressed = false;
	}

	return Key::ERROR_KEY;
}