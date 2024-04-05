#include "../BrainDrainLib/mainMenu.h"

void mainMenu::windowInit() {
    InitWindow(init.screenWidth, init.screenHeight, "BrainDrain");

    SetTargetFPS(60);

    texture = LoadTexture("../assets/button/demoButtonMainMenu.png");

    buttonSize = { (float)texture.width, (float)texture.height };
    playButtonPos = { (init.screenWidth - buttonSize.x) / 2, (init.screenHeight - buttonSize.y) / 2 - 60 };
    settingsButtonPos = { (init.screenWidth - buttonSize.x) / 2, (init.screenHeight - buttonSize.y) / 2 + 50 };
    exitButtonPos = { (init.screenWidth - buttonSize.x) / 2, (init.screenHeight - buttonSize.y) / 2 + 160 };

    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();

            if (CheckCollisionPointRec(mousePosition, { playButtonPos.x, playButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Play button clicked!\n");                
                init.modeSelection();
            }
            else if (CheckCollisionPointRec(mousePosition, { settingsButtonPos.x, settingsButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Settings button clicked!\n");
            }
            else if (CheckCollisionPointRec(mousePosition, { exitButtonPos.x, exitButtonPos.y, buttonSize.x, buttonSize.y })) {
                break;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        Vector2 mousePosition = GetMousePosition();
        bool playHovered = CheckCollisionPointRec(mousePosition, { playButtonPos.x, playButtonPos.y, buttonSize.x, buttonSize.y });
        bool settingsHovered = CheckCollisionPointRec(mousePosition, { settingsButtonPos.x, settingsButtonPos.y, buttonSize.x, buttonSize.y });
        bool exitHovered = CheckCollisionPointRec(mousePosition, { exitButtonPos.x, exitButtonPos.y, buttonSize.x, buttonSize.y });
        
        if (playHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { playButtonPos.x - (buttonSize.x * init.hoverScaleIncrease - buttonSize.x) / 2, playButtonPos.y - (buttonSize.y * init.hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * init.hoverScaleIncrease, buttonSize.y * init.hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, playButtonPos.x, playButtonPos.y, WHITE);

        if (settingsHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { settingsButtonPos.x - (buttonSize.x * init.hoverScaleIncrease - buttonSize.x) / 2, settingsButtonPos.y - (buttonSize.y * init.hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * init.hoverScaleIncrease, buttonSize.y * init.hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, settingsButtonPos.x, settingsButtonPos.y, WHITE);

        if (exitHovered) DrawTexturePro(texture, { 0, 0, buttonSize.x, buttonSize.y }, { exitButtonPos.x - (buttonSize.x * init.hoverScaleIncrease - buttonSize.x) / 2, exitButtonPos.y - (buttonSize.y * init.hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * init.hoverScaleIncrease, buttonSize.y * init.hoverScaleIncrease }, { 0, 0 }, 0, RED);
        else DrawTexture(texture, exitButtonPos.x, exitButtonPos.y, WHITE);
        
        DrawText("Brain Drain", (init.screenWidth - MeasureText("Brain Drain", 40)) / 2, init.screenHeight / 8, 40, BLACK);
        DrawText("Play", playButtonPos.x + (buttonSize.x - MeasureText("Play", 30)) / 2, playButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);
        DrawText("Settings", settingsButtonPos.x + (buttonSize.x - MeasureText("Settings", 30)) / 2, settingsButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);
        DrawText("Exit", exitButtonPos.x + (buttonSize.x - MeasureText("Exit", 30)) / 2, exitButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
}