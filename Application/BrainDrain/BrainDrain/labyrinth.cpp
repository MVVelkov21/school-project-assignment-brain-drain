#include "../BrainDrainLib/labyrinth.h"

void labyrinth::levelBuilder(int subject, int level) {
    levelPath = "../assets/level/level";
    levelPath += to_string(level) + ".png";
    finalLevelPath = levelPath.c_str();
    background = LoadTexture(finalLevelPath);

    playerStill = LoadTexture("../assets/player/boyPlayerDown.png");
    playerLeft = LoadTexture("../assets/player/boyPlayerLeft (1).png");
    playerRight = LoadTexture("../assets/player/boyPlayerRight (1).png");
    playerUp = LoadTexture("../assets/player/boyPlayerUp.png");
    playerDown = LoadTexture("../assets/player/boyPlayerDown.png");    

    colImg = LoadImage("../assets/collision/col_level1.png");
    wallRectangles = map.groupWhitePixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    exitRectangles = map.groupGreenPixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    wordsPos = map.getRedPixelPositions(colImg, colImg.width, colImg.height, background.width, background.height);
    playerPos = map.getYellowPixelPositions(colImg, colImg.width, colImg.height, background.width, background.height);
    UnloadImage(colImg);

    ifstream wordFile("../assets/words/missingWords.txt");
    while (getline(wordFile, word)) {
        words.push_back(word);
    }
    wordFile.close();

    for (size_t i = 0; i < wordsPos.size(); i++) {
        assignedWords.push_back(words[i % words.size()]);
    }

    ifstream emptySentencesFile("../assets/words/emptySentences.txt");    
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
                        std::string chosenWord = pickedUpWords[chosenWordIndex];                       
                        if (chosenWord == words[randLine]) {
                            printf("Correct word! You completed the sentence.\n"); break;
                        }
                        else {
                            printf("Incorrect word.\n"); break;
                        }
                    }
                }
                else {
                    printf("You haven't picked up any words.\n"); break;
                }
            }
        }

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
        //DrawRectangle(playerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale, RED);
        for (size_t i = 0; i < wordsPos.size(); i++) {
            DrawText(assignedWords[i].c_str(), wordsPos[i].x - MeasureText(assignedWords[i].c_str(), 6) / 2, wordsPos[i].y - 3, 6, RED);
        }

        switch (playerDirection) {
        case 1:
            DrawTextureEx(playerLeft, playerPos, 0.0f, playerScale, WHITE);
            break;
        case 2:
            DrawTextureEx(playerRight, playerPos, 0.0f, playerScale, WHITE);
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
        DrawText(randSentence.c_str(), 400 - (MeasureText(randSentence.c_str(), 20) / 2), 10, 20, BLACK);

        EndDrawing();
    }
    wallRectangles.clear();
    exitRectangles.clear();
    wordsPos.clear();
    words.clear();   
    assignedWords.clear();
    pickedUpWords.clear();
    UnloadTexture(background);
    UnloadTexture(playerStill);
    UnloadTexture(playerLeft);
    UnloadTexture(playerRight);
    UnloadTexture(playerUp);
    UnloadTexture(playerDown);
}