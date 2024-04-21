#include "../BrainDrainLib/playerSelection.h"

void levelBuilder()
{
	Texture2D background = LoadTexture("../assets/settingsMenu/settingsMenuBg.png");
	Texture2D girl = LoadTexture("../assets/settingsMenu/girlPlayer.png");
	Texture2D boy = LoadTexture("../assets/settingsMenu/boyPlayer.png");

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(background, 0, 0, WHITE);

		DrawText("Choose a player", (screenWidth - MeasureText("Choose a player", 40)) / 2 + 20, screenHeight / 3.25, 35, RAYWHITE);
		DrawTexture(boy, (GetScreenWidth() / 2) - 200, (GetScreenHeight() / 2) - 20, WHITE);
		DrawTexture(girl, (GetScreenWidth() / 2), (GetScreenHeight() / 2) - 7, WHITE);

		EndDrawing();
	}
}
