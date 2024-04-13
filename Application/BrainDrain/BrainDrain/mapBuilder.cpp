#include "../BrainDrainLib/mapBuilder.h"

vector<Rectangle> mapBuilder::groupWhitePixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
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

vector<Rectangle> mapBuilder::groupGreenPixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
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

vector<Vector2> mapBuilder::getRedPixelPositions(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
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

vector<Rectangle> mapBuilder::groupRedPixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
    vector<Rectangle> rectangles;

    for (int x = 0; x < originalWidth; x++) {
        for (int y = 0; y < originalHeight; y++) {
            Color pixel = GetImageColor(image, x, y);
            if (pixel.r == 255 && pixel.g == 0 && pixel.b == 0) {
                Rectangle rect = { x * scaledWidth / originalWidth, y * scaledHeight / originalHeight, scaledWidth / originalWidth, scaledHeight / originalHeight };
                rectangles.push_back(rect);
            }
        }
    }

    return rectangles;
}

Vector2 mapBuilder::getYellowPixelPositions(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight) {
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