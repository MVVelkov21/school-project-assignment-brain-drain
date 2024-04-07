#pragma once
#include "precompiledHeader.h"

class labyrinth {
private:
	vector<Rectangle> groupWhitePixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);
	vector<Vector2> getRedPixelPositions(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);
	Vector2 getYellowPixelPositions(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);

	string levelPath;
	const char* finalLevelPath;

	Texture2D background;
	Texture2D playerStill;
	Texture2D playerLeft;
	Texture2D playerRight;
	Texture2D playerUp;
	Texture2D playerDown;

	Image colImg;
	vector<Rectangle> wallRectangles;
	vector<Rectangle> exitRectangles;
	vector<Vector2> wordsPos;
	Vector2 playerPos;

	float playerSpeed = 2.5f;
	float playerScale = 0.015f;
	int playerDirection = 0;

	vector<string> words;
	string word;
	vector<string> assignedWords;
	vector<string> pickedUpWords;
public:
	void levelBuilder(int subject, int level);
};
