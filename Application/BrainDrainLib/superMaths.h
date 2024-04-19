#pragma once
#include "precompiledHeader.h"
#include "mapBuilder.h"

class superMaths {
private:
	const int ADDITION = 0;
	const int SUBTRACTION = 1;
	const int MULTIPLICATION = 2;
	const int DIVISION = 3;
	int mathSymbolCount[4] = { 0,0,0,0 };
	string symbol[4]{
		{"ADDITION"},
		{"SUBTRACTION"},
		{"MULTIPLICATION"},
		{"DIVISION"},
	};

	mapBuilder map;

	Texture2D background;
	Texture2D backgroundLeft;
	Texture2D backgroundRight;
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
	vector<Rectangle> walls;
	vector<Rectangle> exit;
	vector<Rectangle> boxes;
	Vector2 playerPos;

	float playerSpeed = 5.0f;
	float playerScale = 0.065f;
	int playerDirection = 0;
	Vector2 playerVelocity = { 0, 0 };
	const float gravity = 0.2f;
	const float jumpForce = 10.0f;
	bool isJumping = false;
	bool onGround = false;	
	Camera2D camera = { 0 };

public:
	void levelBuilder();
};
