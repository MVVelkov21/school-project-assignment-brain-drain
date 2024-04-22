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