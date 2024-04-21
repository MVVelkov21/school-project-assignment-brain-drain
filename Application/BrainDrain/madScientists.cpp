#include "../BrainDrainLib/madScientists.h"

void madScientists::dragDrop(Rectangle& rect, bool& isDragged, float& CordX, float& CordY) {
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
        CordX = rect.x;
        CordY = rect.y;
    }
}

void madScientists::resetElement(Rectangle& el1, Rectangle& final, bool& drag1, float& CordX, float& CordY, int cordTX, int cordTY) {
    if (!(CheckCollisionRecs(el1, final)) && drag1 == false) {
        el1.x = cordTX;
        el1.y = cordTY;
        CordX = el1.x;
        CordY = el1.y;
    }
}

void madScientists::fillTube(Rectangle& el1, Rectangle& el2, Rectangle& final, bool& drag1, bool& drag2, int& c) {
    if (CheckCollisionRecs(el1, final) && drag1 == false) {
        c++;
        el1.x = 170;
        el1.y = 80;
    }
    if (CheckCollisionRecs(el2, final) && drag2 == false) {
        c++;
        el2.x = 260;
        el2.y = 80;
    }
}


void madScientists::levelBuilder() {
    isDraggedEl1 = false, isDraggedEl2 = false;
    tube = LoadTexture("../assets/madScientists/testTube.png");
    tubeHalf = LoadTexture("../assets/madScientists/tubeStage2.png");
    tubeFull = LoadTexture("../assets/madScientists/tubeStage3.png");
    H = LoadTexture("../assets/madScientists/H.png");
    C = LoadTexture("../assets/madScientists/C.png");
    x1 = 170, y1 = 80, x2 = 280, y2 = 80;
    fillCounter = 0;
    tubePos = { 200, 250 };
    tubeHitBox = { 220, 267, 120, 120 };
    Element1 = { x1, y1, 80, 80};
    Element2 = { x2, y2, 80, 80 };
    background = LoadTexture("../assets/madScientists/madScientists2.png");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        resetElement(Element1, tubeHitBox, isDraggedEl1, x1, y1, 170, 80);
        resetElement(Element2, tubeHitBox, isDraggedEl2, x2, y2, 280, 80);
        fillTube(Element1, Element2, tubeHitBox, isDraggedEl1, isDraggedEl2, fillCounter);
        dragDrop(Element1, isDraggedEl1, x1, y1);
        if (isDraggedEl1) {
            isDraggedEl2 = false;
        }
        dragDrop(Element2, isDraggedEl2, x2, y2);

        if (fillCounter > 2) {
            fillCounter = 2;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        DrawRectangleRec(tubeHitBox, GREEN);
        DrawRectangleRec(Element1, BLUE);
        DrawRectangleRec(Element2, RED);

        DrawTexture(H, x1, y1, RAYWHITE);
        DrawTexture(C, x2, y2, RAYWHITE);
        if (fillCounter == 0)
            DrawTextureV(tube, tubePos, RAYWHITE);
        else if (fillCounter == 1) {
            DrawTextureV(tubeHalf, tubePos, RAYWHITE);
        }
        else if (fillCounter == 2) {
            DrawTextureV(tubeFull, tubePos, RAYWHITE);
        }

        EndDrawing();
    }
    UnloadTexture(background);
}