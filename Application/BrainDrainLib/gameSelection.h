#pragma once
#include "precompiledHeader.h"
#include "superMaths.h"
#include "madScientists.h"
#include "labyrinth.h"

class gameSelection {
private:
	labyrinth english;
	superMaths maths;
	madScientists chem;

	Texture2D texture;

	Vector2 buttonSize;
	Vector2 bgButtonPos;
	Vector2 mathButtonPos;
	Vector2 chemButtonPos;

	bool skipFrame = false;
public:
	const int screenWidth = 800;
	const int screenHeight = 450;
	const float hoverScaleIncrease = 1.1f;

	void modeSelection();
};
