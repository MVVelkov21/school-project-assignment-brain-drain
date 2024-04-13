#include "../BrainDrainLib/gameSelection.h"

void gameSelection::modeSelection() {
    texture = LoadTexture("../assets/button/demoButtonSubjects.png");

    buttonSize = { (float)texture.width, (float)texture.height };
    bgButtonPos = { (screenWidth - buttonSize.x) / 2 - 250, (screenHeight - buttonSize.y) / 2 };
    mathButtonPos = { (screenWidth - buttonSize.x) / 2, (screenHeight - buttonSize.y) / 2 };
    chemButtonPos = { (screenWidth - buttonSize.x) / 2 + 250, (screenHeight - buttonSize.y) / 2 };

    while (!WindowShouldClose()) {        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && skipFrame == 1) {
            Vector2 mousePosition = GetMousePosition();

            if (CheckCollisionPointRec(mousePosition, { bgButtonPos.x, bgButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("English button clicked!\n");
                english.levelBuilder(0);
            }
            else if (CheckCollisionPointRec(mousePosition, { mathButtonPos.x, mathButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Maths button clicked!\n");
                maths.levelBuilder();
            }
            else if (CheckCollisionPointRec(mousePosition, { chemButtonPos.x, chemButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Chemistry button clicked!\n");
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 mousePosition = GetMousePosition();
        bool playHovered = CheckCollisionPointRec(mousePosition, { bgButtonPos.x, bgButtonPos.y, buttonSize.x, buttonSize.y });
        bool settingsHovered = CheckCollisionPointRec(mousePosition, { mathButtonPos.x, mathButtonPos.y, buttonSize.x, buttonSize.y });
        bool exitHovered = CheckCollisionPointRec(mousePosition, { chemButtonPos.x, chemButtonPos.y, buttonSize.x, buttonSize.y });

        if (playHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { bgButtonPos.x - (buttonSize.x * hoverScaleIncrease - buttonSize.x) / 2, bgButtonPos.y - (buttonSize.y * hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * hoverScaleIncrease, buttonSize.y * hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, bgButtonPos.x, bgButtonPos.y, WHITE);

        if (settingsHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { mathButtonPos.x - (buttonSize.x * hoverScaleIncrease - buttonSize.x) / 2, mathButtonPos.y - (buttonSize.y * hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * hoverScaleIncrease, buttonSize.y * hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, mathButtonPos.x, mathButtonPos.y, WHITE);

        if (exitHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { chemButtonPos.x - (buttonSize.x * hoverScaleIncrease - buttonSize.x) / 2, chemButtonPos.y - (buttonSize.y * hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * hoverScaleIncrease, buttonSize.y * hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, chemButtonPos.x, chemButtonPos.y, WHITE);

        DrawText("Choose a subject", (screenWidth - MeasureText("Choose a subject", 40)) / 2, screenHeight / 8, 40, BLACK);
        DrawText("English", bgButtonPos.x + (buttonSize.x - MeasureText("English", 30)) / 2, bgButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);
        DrawText("Mathematics", mathButtonPos.x + (buttonSize.x - MeasureText("Mathematics", 30)) / 2, mathButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);
        DrawText("Chemistry", chemButtonPos.x + (buttonSize.x - MeasureText("Chemistry", 30)) / 2, chemButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);

        EndDrawing();

        skipFrame = 1;
    }

    UnloadTexture(texture);
}