#include "../BrainDrainLib/precompiledHeader.h"
#include "../BrainDrainLib/mainMenu.h"

void mainMenu::windowInit() {
    InitWindow(screenWidth, screenHeight, "BrainDrain");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }
    CloseWindow();
}