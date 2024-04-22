#pragma once
#include "precompiledHeader.h"
#include "mapBuilder.h"

class riddleRoute {
private:
	mapBuilder map;
	
	int choice = 0;

	Texture2D background;
	Texture2D playerStill;
	Texture2D playerLeft[4];
	Texture2D playerRight[4];
	Texture2D playerUp;
	Texture2D playerDown;

	int frameCounter = 0;
	int frameSpeed = 8;
	int maxFrames = 3;
	int currentFrame = 0;

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

public:
	void printMessage(const char* msg);
	void levelBuilder();
};
