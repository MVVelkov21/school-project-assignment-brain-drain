#include "../BrainDrainLib/superMaths.h"

void superMaths::loadProblemsAndSymbols(string& problemFile, string& symbolFile) {
    ifstream problemStream(problemFile);
    ifstream symbolStream(symbolFile);    

    while (getline(problemStream, line)) {
        problems.push_back(line);
    }
    problemStream.close();

    while (getline(symbolStream, line)) {
        symbols.push_back(line);
        if (symbols.size() == 3) {
            symbolsByProblem.push_back(symbols);
            symbols.clear();
        }
    }
    symbolStream.close();

    while (!WindowShouldClose()) {
        srand(time(nullptr));
        int randomIndex = rand() % problems.size();
        string selectedProblem = problems[randomIndex];
        vector<string> selectedSymbols = symbolsByProblem[randomIndex];

        problemUnsolved = 0;
        while (problemUnsolved == 0) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Solve the equation", 400 - MeasureText("Solve the equation", 30) / 2, 100, 30, RED);
            DrawText(selectedProblem.c_str(), 400 - MeasureText(selectedProblem.c_str(), 20) / 2, 170, 20, BLACK);
            DrawText("1.", 100 - MeasureText("1.", 20), 250, 20, BLACK);
            DrawText("2.", 300 - MeasureText("2.", 20), 250, 20, BLACK);
            DrawText("3.", 500 - MeasureText("3.", 20), 250, 20, BLACK);
            DrawText("4.", 700 - MeasureText("4.", 20), 250, 20, BLACK);
            DrawText("+", 100 - MeasureText("+", 35), 280, 50, BLACK);
            DrawText("-", 300 - MeasureText("-", 35), 280, 50, BLACK);
            DrawText("*", 500 - MeasureText("*", 35), 280, 50, BLACK);
            DrawText("/", 700 - MeasureText("/", 35), 280, 50, BLACK);
            for (size_t i = 0; i < 4; i++) {
                DrawText(symbol[i].c_str(), 10, 20 + i * 20, 20, BLACK);
                string count = to_string(mathSymbolCount[i]);
                DrawText(count.c_str(), MeasureText(symbol[i].c_str(), 20) + 20, 20 + i * 20, 20, RED);
            }
            DrawText("YOUR ANSWER:", (GetScreenWidth() - MeasureText("YOUR ANSWER:", 30)) / 2, 340, 30, RED);
            for (size_t i = 0; i < playerInput.size(); i++) {
                DrawText(playerInput.substr(i, 1).c_str(), (GetScreenWidth() - (MeasureText(playerInput.substr(i, 1).c_str(), 20) + 60)) / 2.0f + i * 20, 380, 20, BLACK);
            }
            EndDrawing();
            if (IsKeyPressed(KEY_ESCAPE)) {
                problemUnsolved = 2;
                break; 
            }
            if (playerInput.length() < 3) {
                if (IsKeyPressed(KEY_ONE)) {
                    if (mathSymbolCount[0] > 0) {
                        playerInput.push_back('+');
                        mathSymbolCount[0]--;
                    }
                    else {
                        cout << "No more additions left!!" << endl;
                    }
                }
                else if (IsKeyPressed(KEY_TWO)) {
                    if (mathSymbolCount[1] > 0) {
                        playerInput.push_back('-');
                        mathSymbolCount[1]--;
                    }
                    else {
                        cout << "No more subtractions left!!" << endl;
                    }
                }
                else if (IsKeyPressed(KEY_THREE)) {
                    if (mathSymbolCount[2] > 0) {
                        playerInput.push_back('*');
                        mathSymbolCount[2]--;
                    }
                    else {
                        cout << "No more multiplications left!!" << endl;
                    }
                }
                else if (IsKeyPressed(KEY_FOUR)) {
                    if (mathSymbolCount[3] > 0) {
                        playerInput.push_back('/');
                        mathSymbolCount[3]--;
                    }
                    else {
                        cout << "No more divisions left!!" << endl;
                    }
                }
            }
            if (IsKeyPressed(KEY_ENTER)) {
                if (playerInput == selectedSymbols[0] + selectedSymbols[1] + selectedSymbols[2] && mathSymbolCount[0] > 0 && mathSymbolCount[1] > 0 && mathSymbolCount[2] > 0 && mathSymbolCount[3] > 0) {                    
                    endScreen.printMessage("Congrats! You solved the problem!");
                    break;
                }
                else {                    
                    cout << "Incorrect. Please try again." << endl;
                    playerInput = "";
                    problemUnsolved = 1;
                }
            }
        }
        if (problemUnsolved == 0 || problemUnsolved == 2) break;
    }
}

void superMaths::levelBuilder() {
    for (int i = 0; i < 4; i++) mathSymbolCount[i] = 0;
    problemUnsolved = 1;

    background = LoadTexture("../assets/superMath/superMath.png");
    backgroundLeft = LoadTexture("../assets/superMath/superMathBgLeft.png");
    backgroundRight = LoadTexture("../assets/superMath/superMathBgRight.png");

    ifstream inFile("../assets/config.txt");
    if (inFile.is_open()) {
        inFile >> choice;
        inFile.close();
    }

    playerStill = LoadTexture(("../assets/player/" + to_string(choice) + "PlayerDown.png").c_str());
    for (int i = 0; i < 4; i++) {
        string left = "../assets/player/" + to_string(choice) + "PlayerLeft" + to_string(i) + ".png";
        string right = "../assets/player/" + to_string(choice) + "PlayerRight" + to_string(i) + ".png";
        playerLeft[i] = LoadTexture(left.c_str());
        playerRight[i] = LoadTexture(right.c_str());
    }
    playerUp = LoadTexture(("../assets/player/" + to_string(choice) + "PlayerUp.png").c_str());
    playerDown = LoadTexture(("../assets/player/" + to_string(choice) + "PlayerDown.png").c_str());

    colImg = LoadImage("../assets/collision/col_superMath.png");
    walls = map.groupWhitePixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    exit = map.groupGreenPixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    boxes = map.groupRedPixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    playerPos = map.getYellowPixelPositions(colImg, colImg.width, colImg.height, background.width, background.height);
    startingPos = playerPos;
    UnloadImage(colImg);    
    
    camera.target = { (float)background.width / 2, (float)background.height / 2 };
    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    while (!WindowShouldClose()) {
        Vector2 previousPlayerPos = playerPos;
        problemUnsolved = 1;

        if (IsKeyDown(KEY_SPACE) && onGround) {
            playerVelocity.y = -jumpForce;
            onGround = false;
        }

        if (IsKeyDown(KEY_A)) {
            playerVelocity.x = -playerSpeed;
            playerDirection = 1;
        }
        else if (IsKeyDown(KEY_D)) {
            playerVelocity.x = playerSpeed;
            playerDirection = 2;
        }
        else {
            playerVelocity.x = 0;
            playerDirection = 0;
        }
        
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
            frameCounter++;
            if (frameCounter >= (60 / frameSpeed)) {
                frameCounter = 0;
                currentFrame++;
                if (currentFrame > maxFrames) currentFrame = 0;
            }
        }
        else {
            frameCounter = 0;
            currentFrame = 0;
        }

        if (!onGround) {
            playerVelocity.y += gravity;
        }
        
        playerPos.x += playerVelocity.x;
        playerPos.y += playerVelocity.y;
                
        for (size_t i = 0; i < boxes.size(); i++) {
            if (CheckCollisionRecs({ playerPos.x, previousPlayerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, boxes[i])) {
                playerPos.x = previousPlayerPos.x;
                break;
            }
        }
        
        for (size_t i = 0; i < boxes.size(); i++) {
            if (CheckCollisionRecs({ previousPlayerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, boxes[i])) {
                playerPos.y = previousPlayerPos.y;
                if (playerVelocity.y > 0) {
                    onGround = true;
                    playerVelocity.y = 0;
                }                
                break;
            }
        }
        
        if (playerVelocity.y < 0) {
            Rectangle playerAboveRect = { playerPos.x, playerPos.y - 1, playerStill.width * playerScale, 1 };
            for (size_t i = 0; i < boxes.size(); i++) {
                if (CheckCollisionRecs(playerAboveRect, boxes[i])) {
                    playerVelocity.y = 0;                    
                    srand(time(NULL));
                    int randomIndex = rand() % 4;
                    mathSymbolCount[randomIndex]++;
                    break;
                }
            }
        }        
        
        if (playerVelocity.y < 0) {
            for (size_t i = 0; i < walls.size(); i++) {
                if (CheckCollisionRecs({ playerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, walls[i])) {
                    playerVelocity.y = 0;                    
                    break;
                }
            }
        }

        for (size_t i = 0; i < walls.size(); i++) {
            if (CheckCollisionRecs({ playerPos.x, previousPlayerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, walls[i])) {
                playerPos.x = previousPlayerPos.x;
                break;
            }
        }
        
        bool collidedWithWallY = false;
        for (size_t i = 0; i < walls.size(); i++) {
            if (CheckCollisionRecs({ previousPlayerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, walls[i])) {
                playerPos.y = previousPlayerPos.y;
                if (playerVelocity.y > 0) {
                    onGround = true;
                    playerVelocity.y = 0;
                }
                collidedWithWallY = true;
                break;
            }
        }
        
        if (!collidedWithWallY && !isJumping) {
            onGround = false;
        }
        
        if (playerVelocity.y < 0) {
            for (size_t i = 0; i < walls.size(); i++) {
                if (CheckCollisionRecs({ playerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, walls[i])) {
                    playerVelocity.y = 0;
                    break;
                }
            }
        }
        for (size_t i = 0; i < exit.size(); i++) {
            if (CheckCollisionRecs({ playerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, exit[i])) {
                string problems = "../assets/superMath/math problems/problems.txt";
                string symbols = "../assets/superMath/math problems/symbols.txt";
                loadProblemsAndSymbols(problems, symbols);
                playerPos = startingPos;
                if(problemUnsolved == 0) break;
            }
        }        
        if (problemUnsolved == 0) break;
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        DrawTexture(backgroundLeft, -backgroundLeft.width, 0, WHITE);
        DrawTexture(backgroundRight, background.width, 0, WHITE);
        DrawTexture(background, 0, 0, WHITE);
        for (size_t i = 0; i < 4; i++) {           
            DrawText(symbol[i].c_str(), 10, 50 + i * 50, 50, BLACK);
            string count = to_string(mathSymbolCount[i]);
            DrawText(count.c_str(), MeasureText(symbol[i].c_str(), 50) + 30, 50 + i * 50, 50, RED);
        }        
        switch (playerDirection) {
        case 1:
            DrawTextureEx(playerLeft[currentFrame], playerPos, 0.0f, playerScale, WHITE);
            break;
        case 2:
            DrawTextureEx(playerRight[currentFrame], playerPos, 0.0f, playerScale, WHITE);
            break;
        case 3:
            DrawTextureEx(playerUp, playerPos, 0.0f, playerScale, WHITE);
            break;
        case 4:
            DrawTextureEx(playerDown, playerPos, 0.0f, playerScale, WHITE);
            break;
        default:
            DrawTextureEx(playerStill, playerPos, 0.0f, playerScale, WHITE);
            break;
        }
        EndMode2D();
        EndDrawing();
    }    
    UnloadTexture(background);
    UnloadTexture(backgroundLeft);
    UnloadTexture(backgroundRight);
    UnloadTexture(playerStill);
    for (int i = 0; i < 4; i++) {
        UnloadTexture(playerLeft[i]);
        UnloadTexture(playerRight[i]);
    }
    UnloadTexture(playerUp);
    UnloadTexture(playerDown);
}
