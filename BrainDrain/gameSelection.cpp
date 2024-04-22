#include "../BrainDrainLib/gameSelection.h"

void gameSelection::modeSelection() {
    background = LoadTexture("../assets/gameSelectionMenu/gameSelectionMenu.png");

    buttonSize = { 162, 216 };
    enButtonPos = { 38, 225};
    mathButtonPos = { enButtonPos.x + buttonSize.x + 47, enButtonPos.y };
    chemButtonPos = { enButtonPos.x + (buttonSize.x + 47) * 2, enButtonPos.y };

    enButtonRect = { enButtonPos.x, enButtonPos.y, buttonSize.x, buttonSize.y };
    mathButtonRect = { mathButtonPos.x, mathButtonPos.y, buttonSize.x, buttonSize.y };
    chemButtonRect = { chemButtonPos.x, chemButtonPos.y, buttonSize.x, buttonSize.y };

    while (!WindowShouldClose()) {        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && skipFrame == 2) {
            Vector2 mousePosition = GetMousePosition();

            if (CheckCollisionPointRec(mousePosition, { enButtonPos.x, enButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("English button clicked!\n");
                english.levelBuilder();
            }
            else if (CheckCollisionPointRec(mousePosition, { mathButtonPos.x, mathButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Maths button clicked!\n");
                maths.levelBuilder();               
            }
            else if (CheckCollisionPointRec(mousePosition, { chemButtonPos.x, chemButtonPos.y, buttonSize.x, buttonSize.y })) {
                printf("Chemistry button clicked!\n");
                chem.levelBuilder();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);

    
        DrawText("English", enButtonPos.x + buttonSize.x / 2 - MeasureText("English", 20) / 2, enButtonPos.y + buttonSize.y / 2 + 20 , 20,  BLACK);

        DrawText("Maths", mathButtonPos.x + buttonSize.x / 2 - MeasureText("Maths", 20) / 2, mathButtonPos.y + buttonSize.y / 2 + 20, 20, BLACK);

        DrawText( "Chemistry",  chemButtonPos.x + buttonSize.x / 2 - MeasureText("Chemistry", 18) / 2, chemButtonPos.y + buttonSize.y / 2 + 20 , 19, BLACK);

        DrawText("Choose a subject", (screenWidth - MeasureText("Choose a subject", 40)) / 2, screenHeight / 3.5 , 40, BLACK);

        EndDrawing();

        skipFrame++;
        if (skipFrame >= 2) skipFrame = 2;
    }
    skipFrame = 0;
    UnloadTexture(background);
}