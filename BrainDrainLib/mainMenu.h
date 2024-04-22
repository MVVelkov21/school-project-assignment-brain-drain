#pragma once
#include "precompiledHeader.h"
#include "gameSelection.h"
#include "playerSelection.h"

class mainMenu {
	Texture2D background;
	Texture2D play;
	Texture2D settings;
	Texture2D exit;
	Texture2D bus;
	Texture2D school;
	Image icon;

	Vector2 playButtonSize;
	Vector2 smallButtonSize;
	Vector2 playButtonPos;
	Vector2 settingsButtonPos;
	Vector2 exitButtonPos;

	playerSelection select;
	gameSelection init;
public:
	void windowInit();
};