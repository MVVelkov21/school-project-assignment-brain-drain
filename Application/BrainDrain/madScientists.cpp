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

void madScientists::fillTube(Rectangle& el1, Rectangle& final, bool& drag1, bool& flag ,int& c, int cordTX, int cordTY) {
    if (CheckCollisionRecs(el1, final) && drag1 == false) {
        c++;
        el1.x = cordTX;
        el1.y = cordTY;
        flag = true;
    }
}


void madScientists::levelBuilder() {
    background = LoadTexture("../assets/madScientists/madScientists2.png");
    tube = LoadTexture("../assets/madScientists/testTube.png");
    tubeHalf = LoadTexture("../assets/madScientists/tubeStage2.png");
    tubeFull = LoadTexture("../assets/madScientists/tubeStage3.png");
    H = LoadTexture("../assets/madScientists/H.png");
    C = LoadTexture("../assets/madScientists/C.png");
    S = LoadTexture("../assets/madScientists/S.png");
    O = LoadTexture("../assets/madScientists/O.png");
    x1 = 170, y1 = 80, x2 = 280, y2 = 80, x3 = 390, y3 = 80, x4 = 500, y4 = 80;
    isDraggedEl1 = false, isDraggedEl2 = false, isDraggedEl3 = false, isDraggedEl4 = false;
    el1Tube = false, el2Tube = false, el3Tube = false, el4Tube = false;
    fillCounter = 0;
    tubePos = { 200, 250 };
    tubeHitBox = { 220, 267, 120, 120 };
    Element1 = { x1, y1, 80, 80};
    Element2 = { x2, y2, 80, 80 };
    Element3 = { x3, y3, 80, 80 };
    Element4 = { x4, y4, 80, 80 };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        resetElement(Element1, tubeHitBox, isDraggedEl1, x1, y1, 170, 80);
        resetElement(Element2, tubeHitBox, isDraggedEl2, x2, y2, 280, 80);
        resetElement(Element3, tubeHitBox, isDraggedEl3, x3, y3, 390, 80);
        resetElement(Element4, tubeHitBox, isDraggedEl4, x4, y4, 500, 80);
        fillTube(Element1, tubeHitBox, isDraggedEl1, el1Tube,fillCounter, 170, 80);
        fillTube(Element2, tubeHitBox, isDraggedEl2, el2Tube,fillCounter, 280, 80);
        fillTube(Element3, tubeHitBox, isDraggedEl3, el3Tube,fillCounter, 390, 80);
        fillTube(Element4, tubeHitBox, isDraggedEl4, el4Tube,fillCounter, 500, 80);
        dragDrop(Element1, isDraggedEl1, x1, y1);
        dragDrop(Element2, isDraggedEl2, x2, y2);
        dragDrop(Element3, isDraggedEl3, x3, y3);
        dragDrop(Element4, isDraggedEl4, x4, y4);

        if (fillCounter > 2) {
            fillCounter = 2;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, WHITE);

        DrawRectangleRec(tubeHitBox, GREEN);

        DrawRectangleRec(Element1, BLUE);
        DrawRectangleRec(Element2, RED);
        DrawRectangleRec(Element3, YELLOW);
        DrawRectangleRec(Element4, PINK);

        DrawTexture(H, x1, y1, RAYWHITE);
        DrawTexture(C, x2, y2, RAYWHITE);
        DrawTexture(S, x3, y3, RAYWHITE);
        DrawTexture(O, x4, y4, RAYWHITE);

        if (fillCounter == 0)
            DrawTextureV(tube, tubePos, RAYWHITE);
        else if (fillCounter == 1) {
            DrawTextureV(tubeHalf, tubePos, RAYWHITE);
        }
        else if (fillCounter == 2) {
            DrawTextureV(tubeFull, tubePos, RAYWHITE);
            if (el1Tube && el4Tube) {
                DrawText("H2O", 200, 250, 24, BLACK); //Wasser
            }
            else if (el1Tube && el2Tube) {
                DrawText("CH4", 200, 250, 24, BLACK); //Methane
            }
            else if (el1Tube && el3Tube) {
                DrawText("H2S", 200, 250, 24, BLACK); //Hydrogen sulfide
            }
            else if (el2Tube && el4Tube) {
                DrawText("CO2", 200, 250, 24, BLACK); //Carbon dioxide
            }
            else if (el3Tube && el4Tube) {
                DrawText("SO2", 200, 250, 24, BLACK); //Sulfur dioxide
            }
            else {
                DrawText("BOOM", 200, 250, 24, BLACK);
            }
        }
        EndDrawing();
    }
    UnloadTexture(background);
}