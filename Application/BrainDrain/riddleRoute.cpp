#include "../BrainDrainLib/riddleRoute.h"

void riddleRoute::printMessage(const char* msg) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(msg, 400 - (MeasureText(msg, 40) / 2), 175, 40, RED);
        DrawText("Press ESC to go back.", 400 - (MeasureText("Press ESC to go back.", 20) / 2), 260, 20, BLACK);

        EndDrawing();
    }
}

void riddleRoute::levelBuilder(int level) {
    remainingGuesses = 3;
    wrongGuesses = 0;
    levelPath = "../assets/riddleRoute/level";
    levelPath += to_string(level) + ".png";
    finalLevelPath = levelPath.c_str();
    background = LoadTexture(finalLevelPath);

    playerStill = LoadTexture("../assets/player/boyPlayerDown.png");
    for (int i = 0; i < 4; i++) {
        string leftFilename = "../assets/player/boyPlayerLeft" + to_string(i) + ".png";
        string rightFilename = "../assets/player/boyPlayerRight" + to_string(i) + ".png";
        playerLeft[i] = LoadTexture(leftFilename.c_str());
        playerRight[i] = LoadTexture(rightFilename.c_str());
    }
    playerUp = LoadTexture("../assets/player/boyPlayerUp.png");
    playerDown = LoadTexture("../assets/player/boyPlayerDown.png");    



    colImg = LoadImage("../assets/collision/col_level1.png");
    wallRectangles = map.groupWhitePixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    exitRectangles = map.groupGreenPixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    wordsPos = map.getRedPixelPositions(colImg, colImg.width, colImg.height, background.width, background.height);
    playerPos = map.getYellowPixelPositions(colImg, colImg.width, colImg.height, background.width, background.height);
    UnloadImage(colImg);

    X = LoadTexture("../assets/error.png");

    ifstream wordFile("../assets/riddleRoute/words/missingWords.txt");
    while (getline(wordFile, word)) {
        words.push_back(word);
    }
    wordFile.close();

    for (size_t i = 0; i < wordsPos.size(); i++) {
        assignedWords.push_back(words[i % words.size()]);
    }

    ifstream emptySentencesFile("../assets/riddleRoute/words/emptySentences.txt");    
    while (getline(emptySentencesFile, sentence)) {
        emptySentences.push_back(sentence);
    }
    emptySentencesFile.close();

    srand(time(NULL));
    int randLine = rand() % min((int)(assignedWords.size()), (int)(emptySentences.size()));
    randSentence = emptySentences[randLine];
    
    camera.target = playerPos;
    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {        
        Vector2 previousPlayerPos = playerPos;

        if (IsKeyDown(KEY_W)) {
            playerPos.y -= playerSpeed;
            playerDirection = 3;
        }
        else if (IsKeyDown(KEY_S)) {
            playerPos.y += playerSpeed;
            playerDirection = 4;
        }
        else if (IsKeyDown(KEY_A)) {
            playerPos.x -= playerSpeed;
            playerDirection = 1;
        }
        else if (IsKeyDown(KEY_D)) {
            playerPos.x += playerSpeed;
            playerDirection = 2;
        }
        else {
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
        
        Rectangle playerRect = { playerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale };
        for (size_t i = 0; i < wallRectangles.size(); i++) {
            if (CheckCollisionRecs(playerRect, wallRectangles[i])) {                
                playerPos = previousPlayerPos;               
            }
        }

        for (size_t i = 0; i < exitRectangles.size(); i++) {
            if (CheckCollisionRecs(playerRect, exitRectangles[i])) {                
                if (!pickedUpWords.empty()) {
                    bool wordChosen = false;
                    int chosenWordIndex = -1;
                    
                    for (size_t j = 0; j < pickedUpWords.size(); j++) {
                        Rectangle wordRect = { 10, 10 + j * 20, MeasureText(pickedUpWords[j].c_str(), 20), 20 };
                        if (CheckCollisionPointRec(GetMousePosition(), wordRect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            chosenWordIndex = (int)j;
                            wordChosen = true;
                            break;
                        }
                    }
                    
                    if (wordChosen) {
                        string chosenWord = pickedUpWords[chosenWordIndex];                       
                        if (chosenWord == words[randLine]) {
                            printf("You completed the sentence.\n");
                            wrongGuesses = -1;
                            printMessage("Congrats! You completed the sentence.");
                            break;
                        }
                        else {
                            printf("Incorrect word.\n");
                            remainingGuesses--;
                            wrongGuesses++;
                            if (remainingGuesses == 0) {
                                printf("You don't have more tries.\n"); 
                                printMessage("You don't have more tries.");
                                break;                                
                            }                            
                            break;
                        }
                    }
                }
                else {
                    printf("You haven't picked up any words.\n"); break;
                }
            }
        }
        if (remainingGuesses == 0 || wrongGuesses == -1)break;

        for (size_t i = 0; i < wordsPos.size(); i++) {
            Rectangle wordRect = { wordsPos[i].x - 20, wordsPos[i].y - 10, MeasureText(assignedWords[i].c_str(), 20), 30 };
            if (CheckCollisionPointRec(playerPos, wordRect)) {                
                if (find(pickedUpWords.begin(), pickedUpWords.end(), assignedWords[i]) == pickedUpWords.end()) {
                    pickedUpWords.push_back(assignedWords[i]);                    
                    assignedWords.erase(assignedWords.begin() + i);
                    wordsPos.erase(wordsPos.begin() + i);
                    break;
                }
            }
        }

        camera.target = playerPos;
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawTexture(background, 0, 0, WHITE);                
        for (size_t i = 0; i < wordsPos.size(); i++) {
            DrawText(assignedWords[i].c_str(), wordsPos[i].x - MeasureText(assignedWords[i].c_str(), 6) / 2, wordsPos[i].y - 3, 6, RED);
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

        for (size_t i = 0; i < pickedUpWords.size(); i++) {
            DrawText(pickedUpWords[i].c_str(), 10, 10 + i * 20, 20, BLACK);
        }

        for (size_t i = 0; i < wrongGuesses; i++) {
            DrawTexture(X, 790 - X.width - i * X.width, 440 - X.height, WHITE);
        }

        DrawText(randSentence.c_str(), 400 - (MeasureText(randSentence.c_str(), 20) / 2), 10, 20, BLACK);

        EndDrawing();
    }
    wallRectangles.clear();
    exitRectangles.clear();
    wordsPos.clear();
    words.clear();   
    assignedWords.clear();
    pickedUpWords.clear();
    UnloadTexture(X);
    UnloadTexture(background);
    UnloadTexture(playerStill);
    for (int i = 0; i < 4; i++) {
        UnloadTexture(playerLeft[i]);
        UnloadTexture(playerRight[i]);
    }
    UnloadTexture(playerUp);
    UnloadTexture(playerDown);
}