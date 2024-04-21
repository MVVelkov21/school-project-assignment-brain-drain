#include "../BrainDrainLib/playerSelection.h"

void levelBuilder()
{
	Texture2D background = LoadTexture("../assets/settingsMenu/settingsMenuBg.png");
	
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(background, 0, 0, WHITE);
		EndDrawing();
	}
}
