#pragma once
#include "pch.h"
#include <fstream>
#include <string>
#include <vector>
#include "CppUnitTest.h"
#include "../BrainDrainLib/precompiledHeader.h"
#include "../raylib/include/raylib.h"
#include "../BrainDrainLib/superMaths.h"
#include "../BrainDrainLib/riddleRoute.h"
#include "../BrainDrainLib/madScientists.h"
#include "../BrainDrainLib/playerSelection.h"
#include "../BrainDrainLib/gameSelection.h"

void reworkedPrintMessage(const char* msg)
{
    std::cout << msg << std::endl;
}

void reworkedModeSelection()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        break;
    }
}

void reworkedDragDrop(bool& isDragged, bool isMouseButtonPressed, bool isMouseOver)
{
    if (isMouseButtonPressed && isMouseOver)
    {
        isDragged = true;
    }
    else
    {
        isDragged = false;
    }
}

void reworkedResetElement(bool& isCollision1, bool& isCollision2, bool& isDragged1, bool& isDragged2, int& el1X, int& el1Y, int& el2X, int& el2Y) {
    if (!isCollision1 && !isDragged1)
    {
        el1X = 170;
        el1Y = 80;
    }
    if (!isCollision2 && !isDragged2)
    {
        el2X = 260;
        el2Y = 80;
    }
}