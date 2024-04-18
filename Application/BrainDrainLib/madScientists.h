#pragma once
#include "precompiledHeader.h"

class madScientists {
	private:
		float heldX, heldY;
		Texture2D tube;
		Rectangle Element1, Element2;
		Vector2 tubePos, El1Pos, El2Pos, RecSize;
	public: 
		void levelBuilder();
};
