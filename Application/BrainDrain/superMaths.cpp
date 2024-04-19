#include "../BrainDrainLib/superMaths.h"

void superMaths::levelBuilder() {
    background = LoadTexture("../assets/superMath/superMath.png");
    backgroundLeft = LoadTexture("../assets/superMath/superMathBgLeft.png");
    backgroundRight = LoadTexture("../assets/superMath/superMathBgRight.png");

    playerStill = LoadTexture("../assets/player/boyPlayerDown.png");
    for (int i = 0; i < 4; i++) {
        string leftFilename = "../assets/player/boyPlayerLeft" + to_string(i) + ".png";
        string rightFilename = "../assets/player/boyPlayerRight" + to_string(i) + ".png";        
        playerLeft[i] = LoadTexture(leftFilename.c_str());
        playerRight[i] = LoadTexture(rightFilename.c_str());
    }
    playerUp = LoadTexture("../assets/player/boyPlayerUp.png");
    playerDown = LoadTexture("../assets/player/boyPlayerDown.png");

    colImg = LoadImage("../assets/collision/col_superMath1.png");
    walls = map.groupWhitePixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    exit = map.groupGreenPixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    boxes = map.groupRedPixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    playerPos = map.getYellowPixelPositions(colImg, colImg.width, colImg.height, background.width, background.height);
    UnloadImage(colImg);    

    camera.target = { (float)background.width / 2, (float)background.height / 2 };
    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    while (!WindowShouldClose()) {
        Vector2 previousPlayerPos = playerPos;


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
        
        bool collidedWithBoxX = false;
        for (size_t i = 0; i < boxes.size(); i++) {
            if (CheckCollisionRecs({ playerPos.x, previousPlayerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, boxes[i])) {
                playerPos.x = previousPlayerPos.x;
                collidedWithBoxX = true;
                break;
            }
        }

        bool collidedWithBoxY = false;
        for (size_t i = 0; i < boxes.size(); i++) {
            if (CheckCollisionRecs({ previousPlayerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, boxes[i])) {
                playerPos.y = previousPlayerPos.y;
                if (playerVelocity.y > 0) {
                    onGround = true;
                    playerVelocity.y = 0;
                }

                if (playerVelocity.y < 0 && IsKeyDown(KEY_SPACE)) {
                    srand(time(NULL));
                    int randomIndex = rand() % 4;
                    mathSymbolCount[randomIndex]++;                    
                }

                collidedWithBoxY = true;
                break;
            }
        }

        bool collidedWithWallAbove = false;
        if (playerVelocity.y < 0) {
            for (size_t i = 0; i < walls.size(); i++) {
                if (CheckCollisionRecs({ playerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, walls[i])) {
                    playerVelocity.y = 0;
                    collidedWithWallAbove = true;
                    break;
                }
            }
        }

        if (collidedWithWallAbove && IsKeyDown(KEY_SPACE)) {
            onGround = true;
        }


        bool collidedWithWallX = false;
        for (size_t i = 0; i < walls.size(); i++) {
            if (CheckCollisionRecs({ playerPos.x, previousPlayerPos.y, playerStill.width * playerScale, playerStill.height * playerScale }, walls[i])) {
                playerPos.x = previousPlayerPos.x;
                collidedWithWallX = true;
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

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);
        DrawTexture(backgroundLeft, -backgroundLeft.width, 0, WHITE);
        DrawTexture(backgroundRight, background.width, 0, WHITE);
        DrawTexture(background, 0, 0, WHITE);
        for (size_t i = 0; i < 4; i++) {           
            DrawText(symbol[i].c_str(), 10, 50 + i * 20, 20, BLACK);
            string count = to_string(mathSymbolCount[i]);
            DrawText(count.c_str(), MeasureText(symbol[i].c_str(), 20) + 10, 50 + i * 20, 20, BLACK);
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
