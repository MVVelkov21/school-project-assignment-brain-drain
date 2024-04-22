#include "../BrainDrainLib/gameSelection.h"

void gameSelection::modeSelection() {
    background = LoadTexture("../assets/gameSelectionMenu/gameSelectionMenu.png");
    font = LoadFont("../assets/font/Silkscreen.ttf");


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

        /*Vector2 mousePosition = GetMousePosition();
        bool enHovered = CheckCollisionPointRec(mousePosition, { enButtonPos.x, enButtonPos.y, buttonSize.x, buttonSize.y });
        bool mathHovered = CheckCollisionPointRec(mousePosition, { mathButtonPos.x, mathButtonPos.y, buttonSize.x, buttonSize.y });
        bool chemHovered = CheckCollisionPointRec(mousePosition, { chemButtonPos.x, chemButtonPos.y, buttonSize.x, buttonSize.y });*/

        /*if (enHovered) DrawRectangleRec(enButtonRect, RED);
        else DrawRectangleLines(enButtonRect.x, enButtonRect.y, enButtonRect.width, enButtonRect.height, WHITE);*/
        DrawTextEx(font, "English", { enButtonPos.x + buttonSize.x / 2 - MeasureText("English", 20) / 2 - 10, enButtonPos.y + buttonSize.y / 2 + 20 }, 20, 1, BLACK);

        /*if (mathHovered) DrawRectangleRec(mathButtonRect, RED);
        else DrawRectangleLines(mathButtonRect.x, mathButtonRect.y, mathButtonRect.width, mathButtonRect.height, WHITE);*/
        DrawTextEx(font, "Maths", { mathButtonPos.x + buttonSize.x / 2 - MeasureText("Maths", 20) / 2 - 4, mathButtonPos.y + buttonSize.y / 2 + 20 }, 20, 1, BLACK);

        /*if (chemHovered) DrawRectangleRec(chemButtonRect, RED);
        else DrawRectangleLines(chemButtonRect.x, chemButtonRect.y, chemButtonRect.width, chemButtonRect.height, WHITE);*/
        DrawTextEx(font, "Chemistry", { chemButtonPos.x + buttonSize.x / 2 - MeasureText("Chemistry", 18) / 2 - 10, chemButtonPos.y + buttonSize.y / 2 + 20 }, 17, 1, BLACK);

        DrawText("Choose a subject", (screenWidth - MeasureText("Choose a subject", 40)) / 2, screenHeight / 3.5 , 40, BLACK);

        EndDrawing();

        skipFrame++;
        if (skipFrame >= 2) skipFrame = 2;
    }
    skipFrame = 0;
    UnloadTexture(background);
}