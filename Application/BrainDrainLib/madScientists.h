#pragma once
#include "precompiledHeader.h"

class madScientists {
	private:
		bool isDraggedEl1, isDraggedEl2;
		int fillCounter;
		float x1, y1, x2, y2;
		Texture2D tube, tubeHalf, tubeFull;
		Texture2D background, H, C;
		Rectangle Element1, Element2, tubeHitBox;
		Vector2 tubePos;
	public: 
		void levelBuilder();
		void dragDrop(Rectangle& rect, bool& isDragged, float& CordX, float& CordY);
		void resetElement(Rectangle& el1, Rectangle & final, bool& drag1, float& CordX, float& CordY, int cordTX, int cordTY);
		void fillTube(Rectangle& el1, Rectangle& el2, Rectangle & final, bool& drag1, bool& drag2, int& c);
};
