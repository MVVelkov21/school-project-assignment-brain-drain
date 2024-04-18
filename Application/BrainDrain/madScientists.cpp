#include "../BrainDrainLib/madScientists.h"


void madScientists::levelBuilder() {
    tube = LoadTexture("../assets/madScientists/testTube.png");
    tubePos = { 200, 250 };
    RecSize = { 30, 30 };
    El1Pos = { 170, 80 };
    
    Element1 = { 170, 80, 80, 80};
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(Element1, BLUE);
        DrawTextureV(tube, tubePos , RAYWHITE);

        EndDrawing();
    }
}