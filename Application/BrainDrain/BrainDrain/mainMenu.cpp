#include "../BrainDrainLib/mainMenu.h"

void mainMenu::windowInit() {
    InitWindow(init.screenWidth, init.screenHeight, "BrainDrain");
    icon = LoadImage("../assets/logo.png");
    SetWindowIcon(icon);
    SetTargetFPS(60);

    play = LoadTexture("../assets/button/playButton.png");
    settings[0] = LoadTexture("../assets/button/settingsButton.png");
    settings[1] = LoadTexture("../assets/button/settingsHoverButton.png");
    exit = LoadTexture("../assets/button/exitButton.png");

    buttonSize = { (float)play.width, (float)play.height };
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
        
        if (playHovered) DrawTexturePro(play, { 0, 0, buttonSize.x, buttonSize.y }, { playButtonPos.x - (buttonSize.x * init.hoverScaleIncrease - buttonSize.x) / 2, playButtonPos.y - (buttonSize.y * init.hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * init.hoverScaleIncrease, buttonSize.y * init.hoverScaleIncrease }, { 0, 0 }, 0, WHITE);
        else DrawTexture(play, playButtonPos.x, playButtonPos.y, RED);

        if (settingsHovered) DrawTexturePro(settings[0], {0, 0, buttonSize.x, buttonSize.y}, {settingsButtonPos.x - (buttonSize.x * init.hoverScaleIncrease - buttonSize.x) / 2, settingsButtonPos.y - (buttonSize.y * init.hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * init.hoverScaleIncrease, buttonSize.y * init.hoverScaleIncrease}, {0, 0}, 0, WHITE);
        else DrawTexture(settings[1], settingsButtonPos.x, settingsButtonPos.y, RED);

        if (exitHovered) DrawTexturePro(exit, { 0, 0, buttonSize.x, buttonSize.y }, { exitButtonPos.x - (buttonSize.x * init.hoverScaleIncrease - buttonSize.x) / 2, exitButtonPos.y - (buttonSize.y * init.hoverScaleIncrease - buttonSize.y) / 2, buttonSize.x * init.hoverScaleIncrease, buttonSize.y * init.hoverScaleIncrease }, { 0, 0 }, 0, WHITE);
        else DrawTexture(exit, exitButtonPos.x, exitButtonPos.y, RED);
        
        DrawText("Brain Drain", (init.screenWidth - MeasureText("Brain Drain", 40)) / 2, init.screenHeight / 8, 40, BLACK);

        EndDrawing();
    }

    for(int i = 0; i < 2; i++) UnloadTexture(settings[i]);
    UnloadTexture(exit);
    UnloadTexture(play);
    CloseWindow();
}