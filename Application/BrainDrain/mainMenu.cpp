#include "../BrainDrainLib/mainMenu.h"

void mainMenu::windowInit() {
    InitWindow(init.screenWidth, init.screenHeight, "BrainDrain");
    icon = LoadImage("../assets/logo.png");
    SetWindowIcon(icon);
    SetTargetFPS(60);

    background = LoadTexture("../assets/mainMenu/mainMenu.png");
    play = LoadTexture("../assets/mainMenu/playButton.png");
    settings[0] = LoadTexture("../assets/mainMenu/settingsButton.png");
    settings[1] = LoadTexture("../assets/mainMenu/settingsHoverButton.png");
    exit = LoadTexture("../assets/mainMenu/exitButton.png");
    bus = LoadTexture("../assets/mainMenu/bus.png");
    school = LoadTexture("../assets/mainMenu/school.png");

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
        DrawTexture(background, 0, 0, WHITE);

        Vector2 mousePosition = GetMousePosition();
        bool playHovered = CheckCollisionPointRec(mousePosition, { playButtonPos.x, playButtonPos.y, buttonSize.x, buttonSize.y });
        bool settingsHovered = CheckCollisionPointRec(mousePosition, { settingsButtonPos.x, settingsButtonPos.y, buttonSize.x, buttonSize.y });
        bool exitHovered = CheckCollisionPointRec(mousePosition, { exitButtonPos.x, exitButtonPos.y, buttonSize.x, buttonSize.y });
        
        DrawTexture(bus, (GetScreenWidth() / 2) - 375, (GetScreenHeight() / 2) + 118, WHITE);
        DrawTexture(school, (GetScreenWidth() / 2) + 150, (GetScreenHeight() / 2) - 15, WHITE);

        DrawTexture(settings[0], (GetScreenWidth() / 2) - 390, (GetScreenHeight() / 2) - 215, WHITE);
        
        DrawTexture(exit, (GetScreenWidth() / 2) + 290, (GetScreenHeight() / 2) - 215, WHITE);

        DrawTexture(play, (GetScreenWidth() / 2) - 170, (GetScreenHeight() / 2) + 38, WHITE);

        EndDrawing();
    }

    for(int i = 0; i < 2; i++) UnloadTexture(settings[i]);
    UnloadTexture(exit);
    UnloadTexture(play);
    CloseWindow();
}