#pragma once
#include "precompiledHeader.h"

class mapBuilder {
public:
	vector<Rectangle> groupWhitePixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);
	vector<Vector2> getRedPixelPositions(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);
	vector<Rectangle> groupRedPixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);
	vector<Rectangle> groupGreenPixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);
	Vector2 getYellowPixelPositions(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);
};
