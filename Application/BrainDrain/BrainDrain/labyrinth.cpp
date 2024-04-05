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

void labyrinth::levelBuilder(int subject, int level) {
    string levelPath = "../assets/level/demoRoom";
    levelPath += to_string(level) + ".png";
    const char* finalLevelPath = levelPath.c_str();
    Texture2D background = LoadTexture(finalLevelPath);

    Texture2D playerStill = LoadTexture("../assets/player/girl/girlPlayerStill.png");
    Texture2D playerLeft = LoadTexture("../assets/player/girl/girlPlayerLeft.png");
    Texture2D playerRight = LoadTexture("../assets/player/girl/girlPlayerRight.png");
    Texture2D playerUp = LoadTexture("../assets/player/girl/girlPlayerUp.png");
    Texture2D playerDown = LoadTexture("../assets/player/girl/girlPlayerDown.png");    

    Image colImg = LoadImage("../assets/collision/col_demoRoom.png");
    vector<Rectangle> wallRectangles = groupWhitePixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    UnloadImage(colImg);

    Vector2 playerPos = { 100.0f, 50.0f };
    float playerSpeed = 2.5f;
    float playerScale = 0.015f;
    int playerDirection = 0;

    Camera2D camera = { 0 };
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

        camera.target = playerPos;
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawTexture(background, 0, 0, WHITE);
        //DrawRectangle(playerPos.x, playerPos.y, playerStill.width * playerScale, playerStill.height * playerScale, RED);
        
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


