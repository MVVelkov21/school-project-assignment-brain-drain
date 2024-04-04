#pragma once
#include "precompiledHeader.h"

class gameSelection {
private:
	Texture2D texture;

	Vector2 buttonSize;
	Vector2 playButtonPos;
	Vector2 settingsButtonPos;
	Vector2 exitButtonPos;

public:
	const int screenWidth = 800;
	const int screenHeight = 450;
	const float hoverScaleIncrease = 1.1f;

	void modeSelection();
};
