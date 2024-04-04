#include "../BrainDrainLib/gameSelection.h"

void gameSelection::modeSelection() {    
    texture = LoadTexture("../assets/demoButtonSubjects.png");

    buttonSize = { (float)texture.width, (float)texture.height };
    playButtonPos = { (screenWidth - buttonSize.x) / 2 - 250, (screenHeight - buttonSize.y) / 2 };
    settingsButtonPos = { (screenWidth - buttonSize.x) / 2, (screenHeight - buttonSize.y) / 2 };
    exitButtonPos = { (screenWidth - buttonSize.x) / 2 + 250, (screenHeight - buttonSize.y) / 2 };

    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();

            if (CheckCollisionPointRec(mousePosition, { playButtonPos.x, playButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Bulgarian button clicked!\n");                
            }
            else if (CheckCollisionPointRec(mousePosition, { settingsButtonPos.x, settingsButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Maths button clicked!\n");
            }
            else if (CheckCollisionPointRec(mousePosition, { exitButtonPos.x, exitButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Chemistry button clicked!\n");
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 mousePosition = GetMousePosition();
        bool playHovered = CheckCollisionPointRec(mousePosition, { playButtonPos.x, playButtonPos.y, buttonSize.x, buttonSize.y });
        bool settingsHovered = CheckCollisionPointRec(mousePosition, { settingsButtonPos.x, settingsButtonPos.y, buttonSize.x, buttonSize.y });
        bool exitHovered = CheckCollisionPointRec(mousePosition, { exitButtonPos.x, exitButtonPos.y, buttonSize.x, buttonSize.y });

        if (playHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { playButtonPos.x - (buttonSize.x * hoverScaleIncrease - buttonSize.x) / 2, playButtonPos.y - (buttonSize.y * hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * hoverScaleIncrease, buttonSize.y * hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, playButtonPos.x, playButtonPos.y, WHITE);

        if (settingsHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { settingsButtonPos.x - (buttonSize.x * hoverScaleIncrease - buttonSize.x) / 2, settingsButtonPos.y - (buttonSize.y * hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * hoverScaleIncrease, buttonSize.y * hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, settingsButtonPos.x, settingsButtonPos.y, WHITE);

        if (exitHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { exitButtonPos.x - (buttonSize.x * hoverScaleIncrease - buttonSize.x) / 2, exitButtonPos.y - (buttonSize.y * hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * hoverScaleIncrease, buttonSize.y * hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, exitButtonPos.x, exitButtonPos.y, WHITE);

        DrawText("Choose a subject", (screenWidth - MeasureText("Choose a subject", 40)) / 2, screenHeight / 8, 40, BLACK);
        DrawText("Bulgarian", playButtonPos.x + (buttonSize.x - MeasureText("Bulgarian", 30)) / 2, playButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);
        DrawText("Mathematics", settingsButtonPos.x + (buttonSize.x - MeasureText("Mathematics", 30)) / 2, settingsButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);
        DrawText("Chemistry", exitButtonPos.x + (buttonSize.x - MeasureText("Chemistry", 30)) / 2, exitButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);

        EndDrawing();
    }

    UnloadTexture(texture);
}