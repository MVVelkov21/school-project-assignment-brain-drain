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
    //Check whether the element is dropped in blank space
    if (!(CheckCollisionRecs(el1, final)) && drag1 == false) {
        el1.x = cordTX;
        el1.y = cordTY;
        CordX = el1.x;
        CordY = el1.y;
    }
}

void madScientists::fillTube(Rectangle& el1, Rectangle& final, bool& drag1, bool& flag ,int& c, int cordTX, int cordTY) {
    //Check whether the element is dropped in the tube
    if (CheckCollisionRecs(el1, final) && drag1 == false) {
        c++;
        el1.x = cordTX;
        el1.y = cordTY;
        flag = true;
    }
}

void madScientists::finish(const char* name) {
    //Draw the name of the product
    DrawText(name, 500, 200, 24, BLACK); //Water
    isDraggedEl1 = false, isDraggedEl2 = false, isDraggedEl3 = false, isDraggedEl4 = false;
    DrawTexture(board, 0, 20, RAYWHITE);
}

void drawWords(vector <string> info) {
    //Output the info about the product
    for (size_t i = 0; i < info.size(); i++) {
        DrawText(info[i].c_str(), 12, 40 + i * 20, 17, BLACK);
    }
}

void madScientists::levelBuilder() {
    //Load all the textures
    background = LoadTexture("../assets/madScientists/madScientists2.png");
    tube = LoadTexture("../assets/madScientists/testTube.png");
    tubeHalf = LoadTexture("../assets/madScientists/tubeStage2.png");
    tubeFull = LoadTexture("../assets/madScientists/tubeStage3.png");
    board = LoadTexture("../assets/madScientists/lesson.png");
    H = LoadTexture("../assets/madScientists/H.png");
    C = LoadTexture("../assets/madScientists/C.png");
    S = LoadTexture("../assets/madScientists/S.png");
    O = LoadTexture("../assets/madScientists/O.png");
    Wrong = LoadTexture("../assets/madScientists/X.png");

    x1 = 350, y1 = 50, x2 = 450, y2 = 50, x3 = 545, y3 = 50, x4 = 642, y4 = 50;
    isDraggedEl1 = false, isDraggedEl2 = false, isDraggedEl3 = false, isDraggedEl4 = false;
    el1Tube = false, el2Tube = false, el3Tube = false, el4Tube = false;
    fillCounter = 0;
    tubePos = { 450, 205 };
    tubeHitBox = { 470, 220, 120, 120 };
    Element1 = { x1, y1, 80, 80};
    Element2 = { x2, y2, 80, 80 };
    Element3 = { x3, y3, 80, 80 };
    Element4 = { x4, y4, 80, 80 };
    ResetButton = { 330, 345, 115, 60 };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        resetElement(Element1, tubeHitBox, isDraggedEl1, x1, y1, 350, 50);
        resetElement(Element2, tubeHitBox, isDraggedEl2, x2, y2, 450, 50);
        resetElement(Element3, tubeHitBox, isDraggedEl3, x3, y3, 545, 50);
        resetElement(Element4, tubeHitBox, isDraggedEl4, x4, y4, 642, 50);
        fillTube(Element1, tubeHitBox, isDraggedEl1, el1Tube,fillCounter, 350, 50);
        fillTube(Element2, tubeHitBox, isDraggedEl2, el2Tube,fillCounter, 450, 50);
        fillTube(Element3, tubeHitBox, isDraggedEl3, el3Tube,fillCounter, 545, 50);
        fillTube(Element4, tubeHitBox, isDraggedEl4, el4Tube,fillCounter, 642, 50);
        dragDrop(Element1, isDraggedEl1, x1, y1);
        dragDrop(Element2, isDraggedEl2, x2, y2);
        dragDrop(Element3, isDraggedEl3, x3, y3);
        dragDrop(Element4, isDraggedEl4, x4, y4);

        //Limit how many times the tube can be filled
        if (fillCounter > 2) {
            fillCounter = 2;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        //Draw textures
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(H, x1, y1, RAYWHITE);
        DrawTexture(C, x2, y2, RAYWHITE);
        DrawTexture(S, x3, y3, RAYWHITE);
        DrawTexture(O, x4, y4, RAYWHITE);

        DrawText("Press ESC to leave", 550, 420, 20, BLACK);

        //Draw tube's stages
        if (fillCounter == 0)
            DrawTextureV(tube, tubePos, RAYWHITE);
        else if (fillCounter == 1) {
            DrawTextureV(tubeHalf, tubePos, RAYWHITE);
        }
        else if (fillCounter == 2) {
            DrawTextureV(tubeFull, tubePos, RAYWHITE);
            //Draw a reset button
            DrawRectangleRec(ResetButton, RED);
            DrawText("Reset", 344, 360, 32, BLACK);
            //if element 1 and elements 2 have been put in the tube
            if (el1Tube && el4Tube) {
                finish("H2O");
                //information about the product
                vector <string> info = {
                    {"Water is an inorganic compound with"},
                    {"the chemical formula H2O and it's a"},
                    {"transparent, tasteless, odorless, "},
                    {"and nearly colorless chemical "},
                    {"substance, it is the main constituent "},
                    {"of Earth's hydrosphere and the  "},
                    {"fluids of all known living organisms."}
                };
                drawWords(info);
            }
            else if (el1Tube && el2Tube) {
                finish("CH4");
                vector <string> info = {
                    {"Methane is a chemical compound with"},
                    {"the chemical formula CH4. It is a"},
                    {"group-14 hydride, the simplest alkane,"},
                    {"and the main constituent of natural"},
                    {" gas. The abundance of methane on"},
                    {"Earth makes it an economically"},
                    {"attractive fuel, although capturing"},
                    {"it is hard."}
                };
                drawWords(info);
            }
            else if (el1Tube && el3Tube) {
                finish("H2S");
                vector <string> info = {
                    {"Hydrogen sulfide is a chemical"},
                    {"compound with the formula H2S. It"},
                    {"is a colorless chalcogen-hydride gas"},
                    {"and is poisonous, corrosive, and"},
                    {"flammable, with trace amounts in"},
                    {"ambient atmosphere having a"},
                    {"characteristic foul odor of"},
                    {"rotten eggs."}
                };
                drawWords(info);
            }
            else if (el2Tube && el4Tube) {
                finish("CO2");
                vector <string> info = {
                    {"Carbon dioxide is a chemical"},
                    {"compound with the chemical formula"},
                    {"CO2. It is found as the source"},
                    {"of available carbon in the carbon"},
                    {"cycle, atmospheric CO2 is the"},
                    {"primary carbon source for life on"},
                    {"Earth. In the air, carbon dioxide"},
                    {"is transparent to visible light."}
                };
                drawWords(info);
            }
            else if (el3Tube && el4Tube) {
                finish("SO2");
                vector <string> info = {
                    {"Sulfur dioxide is the chemical"},
                    {"compound with the formula SO2. It"},
                    {"is a toxic gas responsible for the"},
                    {"odor of burnt matches. It is"},
                    {"released by volcanic activity and"},
                    {"is produced as a by-product of"},
                    {"copper extraction and the burning"},
                    {"of sulfur-bearing fossil fuels."}
                };
                drawWords(info);
            }
            else {
                DrawTextureV(Wrong, tubePos, RAYWHITE);
            }
            if (CheckCollisionPointRec(GetMousePosition(), ResetButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                fillCounter = 0;
                el1Tube = false, el2Tube = false, el3Tube = false, el4Tube = false;
            }

        }
        EndDrawing();
    }
    //Unload all textures
    UnloadTexture(background);
    UnloadTexture(tube);
    UnloadTexture(tubeHalf);
    UnloadTexture(tubeFull);
    UnloadTexture(Wrong);
    UnloadTexture(board);
    UnloadTexture(H);
    UnloadTexture(S);
    UnloadTexture(O);
    UnloadTexture(C);
}