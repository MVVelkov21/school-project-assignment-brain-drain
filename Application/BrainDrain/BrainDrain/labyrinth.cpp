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
    Texture2D background = LoadTexture("../assets/demoRoom.png");

    Texture2D playerStill = LoadTexture("../assets/demoPlayerStill.png");
    Texture2D playerLeft = LoadTexture("../assets/demoPlayerLeft.png");
    Texture2D playerRight = LoadTexture("../assets/demoPlayerRight.png");
    Texture2D playerUp = LoadTexture("../assets/demoPlayerUp.png");
    Texture2D playerDown = LoadTexture("../assets/demoPlayerDown.png");

    Image colImg = LoadImage("../assets/col_demoRoom.png");
    vector<Rectangle> wallRectangles = groupWhitePixelsIntoRectangles(colImg, colImg.width, colImg.height, background.width, background.height);
    UnloadImage(colImg);

    Vector2 playerPos = { 100.0f, 50.0f };
    float playerSpeed = 3.0f;
    int playerDirection = 0;

    Camera2D camera = { 0 };
    camera.target = playerPos;
    camera.offset = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
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
        
        camera.target = playerPos;
                
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        DrawTexture(background, 0, 0, WHITE);

        switch (playerDirection) {
        case 1:
            DrawTexture(playerLeft, playerPos.x, playerPos.y, WHITE);
            break;
        case 2:
            DrawTexture(playerRight, playerPos.x, playerPos.y, WHITE);
            break;
        case 3:
            DrawTexture(playerUp, playerPos.x, playerPos.y, WHITE);
            break;
        case 4:
            DrawTexture(playerDown, playerPos.x, playerPos.y, WHITE);
            break;
        default:
            DrawTexture(playerStill, playerPos.x, playerPos.y, WHITE);
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


