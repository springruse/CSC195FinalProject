
#pragma once
#include "raylib.h"
#include "wall.h"
#include <vector>
#include <string>
class Editor {
public:
	Editor();
	~Editor();
	void update();
	void handleJump();
	void draw();
	
	std::vector<Wall> walls;

	const int screenWidth = 1280;
	const int screenHeight = 800;

private:

	float wallTimeSpawn = 0.0f;
	const float wallTimeInterval = 3.0f;
	bool gameOver = false;
	int score = 0;
	int fontSize = 40;
	

	const float gravity = 0.5f;
	float velocityY = 0.0f;
	float positionY = 100.0f;
	float rotation = 0.0f;
	Texture2D birdTexture;

	Sound jump;
	Sound oof;
	Sound ding;
	Sound womp;
};