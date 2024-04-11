#pragma once
#include "precompiledHeader.h"
#include "labyrinth.h"
#include "superMaths.h"

class gameSelection {
private:
	Texture2D texture;

	Vector2 buttonSize;
	Vector2 bgButtonPos;
	Vector2 mathButtonPos;
	Vector2 chemButtonPos;

	labyrinth level;

	bool skipFrame = false;
public:
	const int screenWidth = 800;
	const int screenHeight = 450;
	const float hoverScaleIncrease = 1.1f;

	void modeSelection();
};
