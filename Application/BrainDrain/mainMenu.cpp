#include "../BrainDrainLib/mainMenu.h"

void mainMenu::windowInit() {
    InitWindow(init.screenWidth, init.screenHeight, "BrainDrain");
    icon = LoadImage("../assets/logo.png");
    SetWindowIcon(icon);
    SetTargetFPS(60);

    background = LoadTexture("../assets/mainMenu/mainMenu.png");
    play = LoadTexture("../assets/mainMenu/playButton.png");
    settings = LoadTexture("../assets/mainMenu/settingsButton.png");    
    exit = LoadTexture("../assets/mainMenu/exitButton.png");
    bus = LoadTexture("../assets/mainMenu/bus.png");
    school = LoadTexture("../assets/mainMenu/school.png");

    playButtonSize = { (float)play.width, (float)play.height };
    smallButtonSize = { (float)settings.width, (float)settings.height };
    playButtonPos = { (init.screenWidth - playButtonSize.x) / 2 , (init.screenHeight - playButtonSize.y) / 2 + 170 };
    settingsButtonPos = { (float)init.screenWidth / 2 - 385, (float)init.screenHeight / 2 - 215 };
    exitButtonPos = { (float)init.screenWidth / 2 + 285, (float)init.screenHeight / 2 - 215 };

    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();

            if (CheckCollisionPointRec(mousePosition, { playButtonPos.x, playButtonPos.y, playButtonSize.x, playButtonSize.y })) {
                printf("Play button clicked!\n");                
                init.modeSelection();
            }
            else if (CheckCollisionPointRec(mousePosition, { settingsButtonPos.x, settingsButtonPos.y, smallButtonSize.x, smallButtonSize.y })) {
                printf("Settings button clicked!\n");
            }
            else if (CheckCollisionPointRec(mousePosition, { exitButtonPos.x, exitButtonPos.y, smallButtonSize.x, smallButtonSize.y })) {
                break;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);

        Vector2 mousePosition = GetMousePosition();
        bool playHovered = CheckCollisionPointRec(mousePosition, { playButtonPos.x, playButtonPos.y, playButtonSize.x, playButtonSize.y });
        bool settingsHovered = CheckCollisionPointRec(mousePosition, { settingsButtonPos.x, settingsButtonPos.y, smallButtonSize.x, smallButtonSize.y });
        bool exitHovered = CheckCollisionPointRec(mousePosition, { exitButtonPos.x, exitButtonPos.y, smallButtonSize.x, smallButtonSize.y });
        
        DrawTexture(bus, (GetScreenWidth() / 2) - 375, (GetScreenHeight() / 2) + 118, WHITE);
        DrawTexture(school, (GetScreenWidth() / 2) + 150, (GetScreenHeight() / 2) - 15, WHITE);

        if (playHovered) DrawTexturePro(play, { 0, 0, playButtonSize.x, playButtonSize.y }, { playButtonPos.x - (playButtonSize.x * init.hoverScaleIncrease - playButtonSize.x) / 2, playButtonPos.y - (playButtonSize.y * init.hoverScaleIncrease - playButtonSize.y) / 2, playButtonSize.x * init.hoverScaleIncrease, playButtonSize.y * init.hoverScaleIncrease }, { 0, 0 }, 0, WHITE);
        else DrawTexture(play, playButtonPos.x, playButtonPos.y, WHITE);

        if (settingsHovered) DrawTexturePro(settings, { 0, 0, smallButtonSize.x, smallButtonSize.y }, { settingsButtonPos.x - (smallButtonSize.x * init.hoverScaleIncrease - smallButtonSize.x) / 2, settingsButtonPos.y - (smallButtonSize.y * init.hoverScaleIncrease - smallButtonSize.y) / 2, smallButtonSize.x * init.hoverScaleIncrease, smallButtonSize.y * init.hoverScaleIncrease }, { 0, 0 }, 0, WHITE);
        else DrawTexture(settings, settingsButtonPos.x, settingsButtonPos.y, WHITE);

        if (exitHovered) DrawTexturePro(exit, { 0, 0, smallButtonSize.x, smallButtonSize.y }, { exitButtonPos.x - (smallButtonSize.x * init.hoverScaleIncrease - smallButtonSize.x) / 2, exitButtonPos.y - (smallButtonSize.y * init.hoverScaleIncrease - smallButtonSize.y) / 2, smallButtonSize.x * init.hoverScaleIncrease, smallButtonSize.y * init.hoverScaleIncrease }, { 0, 0 }, 0, WHITE);
        else DrawTexture(exit, exitButtonPos.x, exitButtonPos.y, WHITE);

        EndDrawing();
    }

    UnloadTexture(settings);
    UnloadTexture(exit);
    UnloadTexture(play);
    CloseWindow();
}