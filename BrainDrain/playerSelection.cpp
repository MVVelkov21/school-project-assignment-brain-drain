#include "../BrainDrainLib/playerSelection.h"

void playerSelection::characterSelect() {
    background = LoadTexture("../assets/settingsMenu/settingsMenuBg.png");
    girl = LoadTexture("../assets/settingsMenu/girlPlayer.png");
    boy = LoadTexture("../assets/settingsMenu/boyPlayer.png");
    
    choice = -1;

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);

        DrawText("Choose a player", (GetScreenWidth() - MeasureText("Choose a player", 40)) / 2, GetScreenHeight() / 3.25, 40, RAYWHITE);
        DrawTexture(boy, (GetScreenWidth() / 2) - 200, (GetScreenHeight() / 2) - 20, WHITE);
        DrawTexture(girl, (GetScreenWidth() / 2), (GetScreenHeight() / 2) - 7, WHITE);

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {           
            if (CheckCollisionPointRec(mousePos, { (float)(GetScreenWidth() / 2) - 200, (float)(GetScreenHeight() / 2) - 20, (float)boy.width, (float)boy.height })) {
                choice = 0;                
            }            
            else if (CheckCollisionPointRec(mousePos, { (float)(GetScreenWidth() / 2), (float)(GetScreenHeight() / 2) - 7, (float)girl.width, (float)girl.height })) {
                choice = 1;                
            }
        }
    }

    ofstream outFile("../assets/config.txt");
    if (outFile.is_open()) {
        outFile << choice;
        outFile.close();
    }
    else {
        cout << "Error: Unable to open or write to file." << endl;
    }

    UnloadTexture(background);
    UnloadTexture(girl);
    UnloadTexture(boy);
}
