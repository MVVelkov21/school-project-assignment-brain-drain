#pragma once
#include "precompiledHeader.h"

class playerSelection {
private:
    Texture2D background;
    Texture2D girl;
    Texture2D boy;

    bool boyHovered = false;
    bool girlHovered = false;

    int choice = -1;
public:
    void characterSelect();
};