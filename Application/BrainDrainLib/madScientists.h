#pragma once
#include "precompiledHeader.h"

class madScientists {
	private:
		bool isDraggedEl1, isDraggedEl2;
		int fillCounter;
		Texture2D tube, tubeHalf, tubeFull;
		Rectangle Element1, Element2, tubeHitBox;
		Vector2 tubePos;
	public: 
		void levelBuilder();
		void dragDrop(Rectangle& rect, bool& isDragged);
		void resetElement(Rectangle& el1, Rectangle& el2, Rectangle& final, bool& drag1, bool& drag2);
		void fillTube(Rectangle& el1, Rectangle& el2, Rectangle & final, bool& drag1, bool& drag2, int& c);
};
