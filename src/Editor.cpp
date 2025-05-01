#include "Editor.h"
#include <vector>
#include <algorithm>

Editor::~Editor()
{
	UnloadTexture(birdTexture);
	UnloadSound(oof);
	UnloadSound(womp);
	UnloadSound(jump);
	UnloadSound(ding);
	// Unload other resources if needed
}

void Editor::update()
{
	if (gameOver) return;

	if (!gameOver) {
		velocityY += gravity;
		positionY += velocityY;

		if (positionY + birdTexture.height > GetScreenHeight()) { // prevent bird from flying off from bottom of screen
			positionY = GetScreenHeight() - birdTexture.height;
			velocityY = 0;
		}

		if (positionY < 0) { // prevent bird from flying from top of screen
			positionY = 0;
			velocityY = 0;
		}

		rotation = rotation * 0.9f + velocityY * 3.0f * 0.1f; // adjust the rotation + smoothness

		if (rotation < -25.0f) rotation = -25.0f; // rotation limit upward
		if (rotation > 25.0f) rotation = 25.0f; // rotation limit downward


		wallTimeSpawn += GetFrameTime();

		if (wallTimeSpawn > wallTimeInterval) {
			wallTimeSpawn = 0.0f;

			int gapOpening = GetRandomValue(200, 350);
			int wallWidth = 100;
			int minHeight = 100;
			int maxHeight = GetScreenHeight() - gapOpening - minHeight;

			int topHeight = GetRandomValue(minHeight, maxHeight);
			int BottomHeight = topHeight + gapOpening;

			Wall wall;
			wall.topPart = { (float)GetScreenWidth(), 0, (float)wallWidth, (float)topHeight };
			wall.bottomPart = { (float)GetScreenWidth(), (float)BottomHeight, (float)wallWidth, (float)(GetScreenHeight() - BottomHeight) };

			walls.push_back(wall);
		}

		for (auto& wall : walls) {
			wall.topPart.x -= 2;
			wall.bottomPart.x -= 2;

			DrawRectangleRec(wall.topPart, GREEN);
			DrawRectangleRec(wall.bottomPart, GREEN);

			

			Rectangle birdHitbox = { 200, positionY, (float)birdTexture.width, (float)birdTexture.height }; // bird hitbox
			if (CheckCollisionRecs(birdHitbox, wall.topPart) || CheckCollisionRecs(birdHitbox, wall.bottomPart)) { // collision detection against wall with bird
				gameOver = true;
				PlaySound(oof);
				PlaySound(womp);
			}

			if (!wall.passedThrough && (birdHitbox.x > wall.topPart.x + wall.topPart.width)) { // if the user passes through a wall but doesn't touch the wall
				wall.passedThrough = true;
				score++;
				PlaySound(ding);
			}
		}

		std::erase_if(walls, [](const Wall& wall) { // gets rid of walls that are past the screen
			return wall.topPart.x + wall.topPart.width < 0;
			});
	}

}

void Editor::handleJump()
{
	if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		velocityY = -10; // Jump velocity
		PlaySound(jump);

		
	}

}

void Editor::draw()
{
	Vector2 position = { 200, positionY };
	Vector2 origin = { birdTexture.width / 2.0f, birdTexture.height / 2.0f };
	

	DrawTextureEx(birdTexture, position, rotation, 1.0f, WHITE);
	std::string scoreText = TextFormat("Score: %d", score);
	int textWidth = MeasureText(scoreText.c_str(), fontSize);
	DrawText(scoreText.c_str(), (screenWidth - textWidth) / 2, 20, fontSize, WHITE);

	if (gameOver) {
		const char* message = "game over, you hit a wall!";
		int messageWidth = MeasureText(message, fontSize);
		int messageY = 20 + fontSize + 10;
		DrawText(message, (screenWidth - messageWidth) / 2, messageY, fontSize, WHITE); 
	}

}

Editor::Editor() {
	 jump = LoadSound("robloxJump.mp3");
	 oof = LoadSound("oof.mp3");
	 ding = LoadSound("ding.mp3");
	 womp = LoadSound("womp.mp3");
	Image blueBirdImage = LoadImage("blueBird.png");
	ImageResize(&blueBirdImage, 75, 75);
	ImageFlipHorizontal(&blueBirdImage);
	birdTexture = LoadTextureFromImage(blueBirdImage);
	UnloadImage(blueBirdImage);

}
