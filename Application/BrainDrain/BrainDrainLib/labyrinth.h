#pragma once
#include "precompiledHeader.h"

class labyrinth {
private:
	vector<Rectangle> groupWhitePixelsIntoRectangles(Image image, int originalWidth, int originalHeight, int scaledWidth, int scaledHeight);

public:
	void levelBuilder(int subject, int level);
};
