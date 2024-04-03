#include "../BrainDrainLib/precompiledHeader.h"
#include "../BrainDrainLib/mainMenu.h"

void mainMenu::windowInit() {
    InitWindow(screenWidth, screenHeight, "BrainDrain");

    SetTargetFPS(60);

    Texture2D texture = LoadTexture("../assets/demoButton.png");

    Vector2 buttonSize = { (float)texture.width, (float)texture.height };
    Vector2 playButtonPos = { (screenWidth - buttonSize.x) / 2, (screenHeight - buttonSize.y) / 4 - 20};
    Vector2 settingsButtonPos = { (screenWidth - buttonSize.x) / 2, (screenHeight - buttonSize.y) / 2 };
    Vector2 exitButtonPos = { (screenWidth - buttonSize.x) / 2, 3 * (screenHeight - buttonSize.y) / 4 + 20};
    
    while (!WindowShouldClose()) {        
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePosition = GetMousePosition();
           
            if (CheckCollisionPointRec(mousePosition, { playButtonPos.x, playButtonPos.y, buttonSize.x, buttonSize.y })) {                
                printf("Play button clicked!\n");                
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

        if (playHovered) DrawTexture(texture, playButtonPos.x, playButtonPos.y, RED);
        else DrawTexture(texture, playButtonPos.x, playButtonPos.y, WHITE);

        if (settingsHovered) DrawTexture(texture, settingsButtonPos.x, settingsButtonPos.y, RED);
        else DrawTexture(texture, settingsButtonPos.x, settingsButtonPos.y, WHITE);

        if (exitHovered) DrawTexture(texture, exitButtonPos.x, exitButtonPos.y, RED);
        else DrawTexture(texture, exitButtonPos.x, exitButtonPos.y, WHITE);

        DrawText("Play", playButtonPos.x + (buttonSize.x - MeasureText("Play", 30)) / 2, playButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);
        DrawText("Settings", settingsButtonPos.x + (buttonSize.x - MeasureText("Settings", 30)) / 2, settingsButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);
        DrawText("Exit", exitButtonPos.x + (buttonSize.x - MeasureText("Exit", 30)) / 2, exitButtonPos.y + (buttonSize.y - 30) / 2, 30, BLACK);

        EndDrawing();
    }
   
    UnloadTexture(texture);
    CloseWindow();
}