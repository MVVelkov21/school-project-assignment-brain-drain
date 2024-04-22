#pragma once
#include "precompiledHeader.h"

class madScientists {
	private:
		bool isDraggedEl1, isDraggedEl2, isDraggedEl3, isDraggedEl4;
		bool el1Tube, el2Tube, el3Tube, el4Tube;
		int fillCounter;
		float x1, y1, x2, y2, x3, y3, x4, y4;
		Texture2D tube, tubeHalf, tubeFull, board;
		Texture2D background, H, C, S, O;
		Rectangle Element1, Element2, Element3, Element4, tubeHitBox, ResetButton;
		Vector2 tubePos;
	public: 
		void levelBuilder();
		void dragDrop(Rectangle& rect, bool& isDragged, float& CordX, float& CordY);
		void resetElement(Rectangle& el1, Rectangle & final, bool& drag1, float& CordX, float& CordY, int cordTX, int cordTY);
		void fillTube(Rectangle& el1, Rectangle & final, bool& drag1, bool& flag, int& c, int cordTX, int cordTY);
		void finish(const char* name);
};
