#pragma once
#include "raylib.h"
class PlayerBird {
public:

	void jump() {
		if (IsKeyPressed(KEY_SPACE) || (IsKeyPressed(MOUSE_BUTTON_LEFT))) {

		}
	}


private:
	int velocityY = 10;
};