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
    TEST_CLASS(testReworkedPrintMessageTest)
    {
    public:

        TEST_METHOD(reworkedPrintMessageTest)
        {

            const char* message = "This is a test message.";


            reworkedPrintMessage(message);


        }
    };
    TEST_CLASS(testReworkedModeSelection)
    {
    public:


        TEST_METHOD(reworkedModeSelectionTest)
        {

            reworkedModeSelection();


        }
    };
    TEST_CLASS(testMadScientistsreworkedFunctions)
    {
    public:


        TEST_METHOD(reworkedDragDropTest)
        {

            bool isMouseButtonPressed = true;
            bool isMouseOver = true;
            bool isDragged = false;
            reworkedDragDrop(isDragged, isMouseButtonPressed, isMouseOver);
            Assert::IsTrue(isDragged);
        }
        TEST_METHOD(reworkedResetElementTest)
        {

            bool isCollision1 = false;
            bool isCollision2 = true;
            bool isDragged1 = false;
            bool isDragged2 = false;
            int el1X = 200;
            int el1Y = 150;
            int el2X = 300;
            int el2Y = 150;

            reworkedResetElement(isCollision1, isCollision2, isDragged1, isDragged2, el1X, el1Y, el2X, el2Y);

            Assert::AreEqual(170, el1X);
            Assert::AreEqual(80, el1Y);
            Assert::AreEqual(300, el2X);
            Assert::AreEqual(150, el2Y);
        }
        TEST_METHOD(reworkedFillTubeTest)
        {

            bool isCollision1 = true;
            bool isCollision2 = false;
            bool isDragged1 = false;
            bool isDragged2 = true;
            int counter = 0;

            reworkedFillTube(isCollision1, isCollision2, isDragged1, isDragged2, counter);

            Assert::AreEqual(1, counter);
        }
    };
    TEST_CLASS(TestSuperMathsSimpleFunctions)
    {
    public:


        TEST_METHOD(reworkedLoadProblemsAndSymbolsTest)
        {

            vector<string> problems;
            vector<vector<string>> symbolsByProblem;

            reworkedLoadProblemsAndSymbols(problems, symbolsByProblem);

            Assert::AreEqual(static_cast<size_t>(3), problems.size());
            Assert::AreEqual(static_cast<size_t>(3), symbolsByProblem.size());
        }
    };
}