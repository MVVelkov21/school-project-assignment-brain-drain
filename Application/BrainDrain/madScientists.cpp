#include "../BrainDrainLib/madScientists.h"

void madScientists::dragDrop(Rectangle& rect, bool& isDragged) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Check if the mouse is over the rectangle
        if (CheckCollisionPointRec(GetMousePosition(), rect)) {
            isDragged = true;
        }
    }
    // Check if the left mouse button is released
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        isDragged = false;
    }

    // If the rectangle is being dragged, update its position
    if (isDragged) {
        rect.x = GetMouseX() - rect.width / 2;
        rect.y = GetMouseY() - rect.height / 2;
    }
}

void madScientists::resetElement(Rectangle& el1, Rectangle& el2, Rectangle& final, bool& drag1, bool& drag2) {
    if (!(CheckCollisionRecs(el1, final)) && drag1 == false) {
        el1.x = 170;
        el1.y = 80;
    }
    if (!(CheckCollisionRecs(el2, final)) && drag2 == false) {
        el2.x = 260;
        el2.y = 80;
    }
}

void madScientists::levelBuilder() {
    tube = LoadTexture("../assets/madScientists/testTube.png");
    tubePos = { 200, 250 };
    tubeHitBox = { 220, 267, 120, 120 };
    Element1 = { 170, 80, 80, 80};
    Element2 = { 260, 80, 80, 80 };
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        resetElement(Element1, Element2, tubeHitBox, isDraggedEl1, isDraggedEl2);
        dragDrop(Element1, isDraggedEl1);
        dragDrop(Element2, isDraggedEl2);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRec(tubeHitBox, GREEN);
        DrawRectangleRec(Element1, BLUE);
        DrawRectangleRec(Element2, RED);
        DrawTextureV(tube, tubePos , RAYWHITE);

        EndDrawing();
    }
}