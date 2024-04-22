#pragma once
#include "precompiledHeader.h"
#include "superMaths.h"
#include "madScientists.h"
#include "riddleRoute.h"

class gameSelection {
private:
	riddleRoute english;
	superMaths maths;
	madScientists chem;
	Font font;
	Texture2D background;

	Vector2 buttonSize;
	Vector2 enButtonPos;
	Vector2 mathButtonPos;
	Vector2 chemButtonPos;

	Rectangle enButtonRect;
	Rectangle mathButtonRect;
	Rectangle chemButtonRect;

	int skipFrame = 0;
public:
	const float screenWidth = 800;
	const float	 screenHeight = 450;
	const float hoverScaleIncrease = 1.1f;

	void modeSelection();
};
