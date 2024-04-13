#pragma once
#include "precompiledHeader.h"
#include "mapBuilder.h"

class superMaths {
private:
	mapBuilder map;

	Texture2D background;
	Texture2D playerStill;
	Texture2D playerLeft;
	Texture2D playerRight;
	Texture2D playerUp;
	Texture2D playerDown;

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
