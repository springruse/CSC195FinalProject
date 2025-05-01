#pragma once
#include "raylib.h"
class Wall {
public:
	Rectangle topPart;
	Rectangle bottomPart;
	bool passedThrough = false;
private:
};