#include "../BrainDrainLib/labyrinth.h"

vector<Rectangle> labyrinth::groupWhitePixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
    vector<Rectangle> rectangles;

    for (int x = 0; x < originalWidth; x++) {
        for (int y = 0; y < originalHeight; y++) {
            Color pixel = GetImageColor(image, x, y);
            if (pixel.r == 255 && pixel.g == 255 && pixel.b == 255) {
                Rectangle rect = { x * scaledWidth / originalWidth, y * scaledHeight / originalHeight, scaledWidth / originalWidth, scaledHeight / originalHeight };
                rectangles.push_back(rect);
            }
        }
    }

    return rectangles;
}

vector<Rectangle> groupGreenPixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
    vector<Rectangle> rectangles;

    for (int x = 0; x < originalWidth; x++) {
        for (int y = 0; y < originalHeight; y++) {
            Color pixel = GetImageColor(image, x, y);
            if (pixel.r == 0 && pixel.g == 255 && pixel.b == 0) {
                Rectangle rect = { x * scaledWidth / originalWidth, y * scaledHeight / originalHeight, scaledWidth / originalWidth, scaledHeight / originalHeight };
                rectangles.push_back(rect);
            }
        }
    }

    return rectangles;
}

vector<Vector2> labyrinth::getRedPixelPositions(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
    vector<Vector2> redPixelPositions;

    for (int x = 0; x < originalWidth; x++) {
        for (int y = 0; y < originalHeight; y++) {
            Color pixel = GetImageColor(image, x, y);
            if (pixel.r == 255 && pixel.g == 0 && pixel.b == 0) {
                Vector2 position = { x * scaledWidth / originalWidth, y * scaledHeight / originalHeight };
                redPixelPositions.push_back(position);
            }
        }
    }

    return redPixelPositions;
}

Vector2 labyrinth::getYellowPixelPositions(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
    Vector2 yellowPixelPositions = { 0, 0 };

    for (int x = 0; x < originalWidth; x++) {
        for (int y = 0; y < originalHeight; y++) {
            Color pixel = GetImageColor(image, x, y);
            if (pixel.r == 255 && pixel.g == 255 && pixel.b == 0) {
                Vector2 position = { x * scaledWidth / originalWidth, y * scaledHeight / originalHeight };
                yellowPixelPositions = position;
                break;
            }
        }
    }

    return yellowPixelPositions;
}

void labyrinth::levelBuilder(int subject, int level) {
    levelPath = "../assets/level/level";
    levelPath += to_string(level) + ".png";
    finalLevelPath = levelPath.c_str();
    background = LoadTexture(finalLevelPath);

    playerStill = LoadTexture("../assets/player/boyPlayerStill.png");
    playerLeft = LoadTexture("../assets/player/boyPlayerLeft.png");
    playerRight = LoadTexture("../assets/player/boyPlayerRight.png");
    playerUp = LoadTexture("../assets/player/boyPlayerUp.png");
    playerDown = LoadTexture("../assets/player/boyPlayerDown.png");    

    colImg = LoadImage("../assets/collision/col_level1.png");
    wallRectangles = groupWhitePixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    exitRectangles = groupGreenPixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    wordsPos = getRedPixelPositions(colImg, colImg.width, colImg.height, background.width, background.height);
    playerPos = getYellowPixelPositions(colImg, colImg.width, colImg.height, background.width, background.height);
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
    randSentence = emptySentences[rand() % min((int)(assignedWords.size()), (int)(emptySentences.size()))];
    
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
                //func
                printf("Finnish reached \n");
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