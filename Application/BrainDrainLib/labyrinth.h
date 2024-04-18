#pragma once
#include "precompiledHeader.h"
#include "mapBuilder.h"

class labyrinth {
private:
	mapBuilder map;

	string levelPath;
	const char* finalLevelPath;

	Texture2D background;
	Texture2D playerStill;
	Texture2D playerLeft;
	Texture2D playerRight;
	Texture2D playerUp;
	Texture2D playerDown;

	float frameWidthPlayer;
	int maxFramesPlayer;
	int framePlayer = 0;
	float timer = 0.0f;

	Image colImg;
	vector<Rectangle> wallRectangles;
	vector<Rectangle> exitRectangles;
	vector<Vector2> wordsPos;
	Vector2 playerPos;

	float playerSpeed = 2.5f;
	float playerScale = 0.025f;
	int playerDirection = 0;

	vector<string> words;
	string word;
	vector<string> assignedWords;
	vector<string> pickedUpWords;

	string randSentence;
	vector<string> emptySentences;
	string sentence;
	int remainingGuesses;
	int wrongGuesses;
	Texture2D X;

	Camera2D camera = { 0 };

	void printMessage(const char* msg);
	void moveAnimation(float& timer, int& frame, int maxFrames, float frameWidth, Texture2D texture, Vector2& pos);
public:
	void levelBuilder(int level);
};
