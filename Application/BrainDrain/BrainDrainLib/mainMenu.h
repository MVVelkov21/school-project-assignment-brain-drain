#pragma once
#include "precompiledHeader.h"
#include "gameSelection.h"

class mainMenu {
	Texture2D play;
	Texture2D settings[2];
	Texture2D exit;
	Image icon;

	Vector2 buttonSize;
	Vector2 playButtonPos;
	Vector2 settingsButtonPos;
	Vector2 exitButtonPos;

	gameSelection init;
public:
	void windowInit();
};