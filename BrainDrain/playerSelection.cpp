#include "../BrainDrainLib/playerSelection.h"

void playerSelection::characterSelect() {
    background = LoadTexture("../assets/settingsMenu/settingsMenuBg.png");
    girl = LoadTexture("../assets/settingsMenu/girlPlayer.png");
    boy = LoadTexture("../assets/settingsMenu/boyPlayer.png");

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);

        DrawText("Choose a player", (GetScreenWidth() - MeasureText("Choose a player", 40)) / 2, GetScreenHeight() / 3.25, 40, RAYWHITE);

        Vector2 boyPos = { (GetScreenWidth() / 2) - 200, (GetScreenHeight() / 2) - 20 };
        Vector2 girlPos = { (GetScreenWidth() / 2), (GetScreenHeight() / 2) - 7 };

        if (CheckCollisionPointRec(mousePos, { boyPos.x, boyPos.y, (float)boy.width, (float)boy.height })) {
            boyPos.x -= (boy.width * 0.1f) / 2;
            boyPos.y -= (boy.height * 0.1f) / 2;
            DrawTextureEx(boy, boyPos, 0, 1.1f, WHITE);
            boyHovered = true;
        }
        else {
            DrawTexture(boy, boyPos.x, boyPos.y, WHITE);
            boyHovered = false;
        }

        if (CheckCollisionPointRec(mousePos, { girlPos.x, girlPos.y, (float)girl.width, (float)girl.height })) {
            girlPos.x -= (girl.width * 0.1f) / 2;
            girlPos.y -= (girl.height * 0.1f) / 2;
            DrawTextureEx(girl, girlPos, 0, 1.1f, WHITE);
            girlHovered = true;
        }
        else {
            DrawTexture(girl, girlPos.x, girlPos.y, WHITE);
            girlHovered = false;
        }

        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (boyHovered) {
                choice = 0;
            }
            else if (girlHovered) {
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
