#include "../BrainDrainLib/superMaths.h"

void superMaths::levelBuilder() {
    background = LoadTexture("../assets/maze/superMath.png");
    backgroundLeft = LoadTexture("../assets/maze/superMathBgLeft.png");
    backgroundRight = LoadTexture("../assets/maze/superMathBgRight.png");

    playerStill = LoadTexture("../assets/player/boyPlayerDown.png");
    playerLeft = LoadTexture("../assets/player/boyPlayerLeftSideAnimation.png");
    playerRight = LoadTexture("../assets/player/boyPlayerRightSideAnimation.png");
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
        
        if (!onGround) {
            playerVelocity.y += gravity;
        }
        
        playerPos.x += playerVelocity.x;
        playerPos.y += playerVelocity.y;
        
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
        EndDrawing();
    }    
    UnloadTexture(background);
    UnloadTexture(playerStill);
    UnloadTexture(playerLeft);
    UnloadTexture(playerRight);
    UnloadTexture(playerUp);
    UnloadTexture(playerDown);
}
