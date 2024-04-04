#pragma once
#include "precompiledHeader.h"
#include "gameSelection.h"

class mainMenu {
	Texture2D texture;

	Vector2 buttonSize;
	Vector2 playButtonPos;
	Vector2 settingsButtonPos;
	Vector2 exitButtonPos;

	gameSelection init;
public:
	void windowInit();
};