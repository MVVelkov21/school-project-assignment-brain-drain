#include "pch.h"
#include <fstream>
#include <string>
#include <vector>
#include "CppUnitTest.h"
#include "reworkedFunctions.h"
#include "../BrainDrainLib/precompiledHeader.h"
#include "../raylib/include/raylib.h"
#include "../BrainDrainLib/superMaths.h"
#include "../BrainDrainLib/riddleRoute.h"
#include "../BrainDrainLib/madScientists.h"
#include "../BrainDrainLib/playerSelection.h"
#include "../BrainDrainLib/gameSelection.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testFunctions
{
    TEST_CLASS(testrReworkedPrintMessageTest)
    {
    public:

        TEST_METHOD(reworkedPrintMessageTest)
        {

            const char* message = "This is a test message.";


            reworkedPrintMessage(message);


        }
    };
}