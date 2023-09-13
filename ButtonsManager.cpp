#include "ButtonsManager.h"

#define WEIGHT_CHANGE 25
#define WEIGHT_CHECK_ACTIVATION 1
#define MOVE_HOOK_LEFT 2
#define MOVE_HOOK_RIGHT 3
#define MOVE_HOOK_DOWN 4
#define MOVE_HOOK_UP 5
#define CATCH_BLOCK 6
#define DROP_BLOCK 7
#define MAX_WEIGHT_UP 8
#define MAX_WEIGHT_DOWN 9
#define RESTRICT_SQUARE 10 
#define ALLOW_SQUARE 11 
#define RESTRICT_TRIANGLE 12 
#define ALLOW_TRIANGLE 13
#define RESTRICT_CIRCLE 14 
#define ALLOW_CIRCLE 15
#define BEGIN_SIMULATION 16

using namespace std;

ButtonsManager::ButtonsManager(shared_ptr<Crane> crane, shared_ptr<Simulator> simulator, shared_ptr<vector<string>> errorsMessages)
{
	this->crane = crane;
	this->simulator = simulator;
	this->errorsMessages = errorsMessages;
}

void ButtonsManager::createButtons(shared_ptr<HWND> window)
{
	createWeightButtons(window);
	createControlsButtons(window);
	createTypesButtons(window);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"SIMULATE", WS_CHILD | WS_VISIBLE, simulateX,
		simulateY, simulateWidth, simulateHeight, *window, (HMENU)BEGIN_SIMULATION, NULL, NULL);//obramowanie , przycisk, napis, dziecko okna, przycisk jest widoczny, polozenie na ekranie, rozmiary przycisku, funkcja do tego przycisku,parametry nieuzywane(menu i obszar) 
}

void ButtonsManager::handleButtonOption(int id)
{
	try
	{
		switch (id)
		{
		case WEIGHT_CHECK_ACTIVATION:
			crane->switchWeightCheckerActivation();
			break;
		case MAX_WEIGHT_UP:
			crane->increaseMaximumWeight(WEIGHT_CHANGE);
			break;
		case MAX_WEIGHT_DOWN:
			crane->decreaseMaximumWeight(WEIGHT_CHANGE);
			break;
		case ALLOW_TRIANGLE:
			crane->addAllowedType("Triangle");
			break;
		case RESTRICT_TRIANGLE:
			crane->removeAllowedType("Triangle");
			break;
		case ALLOW_SQUARE:
			crane->addAllowedType("Square");
			break;
		case RESTRICT_SQUARE:
			crane->removeAllowedType("Square");
			break;
		case ALLOW_CIRCLE:
			crane->addAllowedType("Circle");
			break;
		case RESTRICT_CIRCLE:
			crane->removeAllowedType("Circle");
			break;
		case CATCH_BLOCK:
			crane->catchBlock();
			break;
		case DROP_BLOCK:
			crane->dropBlock();
			break;
		case MOVE_HOOK_UP:
			crane->moveHookUp();
			break;
		case MOVE_HOOK_DOWN:
			crane->moveHookDown();
			break;
		case MOVE_HOOK_LEFT:
			crane->moveHookLeft();
			break;
		case MOVE_HOOK_RIGHT:
			crane->moveHookRight();
			break;
		case BEGIN_SIMULATION:
			simulator->launchSimulation();
			break;
		default:
			break;
		}
	}
	catch (const exception& error)
	{
		errorsMessages->push_back(error.what());
	}
}

void ButtonsManager::createWeightButtons(shared_ptr<HWND> window)
{
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"WEIGHT", WS_CHILD | WS_VISIBLE, weightX,
		weightY, weightWidth, weightHeight, *window, (HMENU)WEIGHT_CHECK_ACTIVATION, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"+", WS_CHILD | WS_VISIBLE, weightX,
		weightY + weightHeight, weightWidth, weightHeight, *window, (HMENU)MAX_WEIGHT_UP, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"-", WS_CHILD | WS_VISIBLE, weightX,
		weightY + 2 * weightHeight, weightWidth, weightHeight, *window, (HMENU)MAX_WEIGHT_DOWN, NULL, NULL);
}

void ButtonsManager::createControlsButtons(shared_ptr<HWND> window)
{
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"DROP", WS_CHILD | WS_VISIBLE, controlsX,
		controlsY, controlsWidth, controlsHeight, *window, (HMENU)DROP_BLOCK, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"UP", WS_CHILD | WS_VISIBLE, controlsX + controlsWidth,
		controlsY, controlsWidth, controlsHeight, *window, (HMENU)MOVE_HOOK_UP, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"CATCH", WS_CHILD | WS_VISIBLE, controlsX + 2 * controlsWidth,
		controlsY, controlsWidth, controlsHeight, *window, (HMENU)CATCH_BLOCK, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"LEFT", WS_CHILD | WS_VISIBLE, controlsX,
		controlsY + controlsHeight, controlsWidth, controlsHeight, *window, (HMENU)MOVE_HOOK_LEFT, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"DOWN", WS_CHILD | WS_VISIBLE, controlsX + controlsWidth,
		controlsY + controlsHeight, controlsWidth, controlsHeight, *window, (HMENU)MOVE_HOOK_DOWN, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"RIGHT", WS_CHILD | WS_VISIBLE, controlsX + 2 * controlsWidth,
		controlsY + controlsHeight, controlsWidth, controlsHeight, *window, (HMENU)MOVE_HOOK_RIGHT, NULL, NULL);
}

void ButtonsManager::createTypesButtons(shared_ptr<HWND> window)
{
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"SQUARE +", WS_CHILD | WS_VISIBLE, restrictX,
		restrictY, restrictWidth, restrictHeight, *window, (HMENU)ALLOW_SQUARE, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"SQUARE -", WS_CHILD | WS_VISIBLE, restrictX,
		restrictY + restrictHeight, restrictWidth, restrictHeight, *window, (HMENU)RESTRICT_SQUARE, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"TRIANGLE +", WS_CHILD | WS_VISIBLE, restrictX + restrictWidth,
		restrictY, restrictWidth, restrictHeight, *window, (HMENU)ALLOW_TRIANGLE, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"TRIANGLE -", WS_CHILD | WS_VISIBLE, restrictX + restrictWidth,
		restrictY + restrictHeight, restrictWidth, restrictHeight, *window, (HMENU)RESTRICT_TRIANGLE, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"CIRCLE +", WS_CHILD | WS_VISIBLE, restrictX + 2 * restrictWidth,
		restrictY, restrictWidth, restrictHeight, *window, (HMENU)ALLOW_CIRCLE, NULL, NULL);
	CreateWindowEx(WS_EX_CLIENTEDGE, L"Button", L"CIRCLE -", WS_CHILD | WS_VISIBLE, restrictX + 2 * restrictWidth,
		restrictY + restrictHeight, restrictWidth, restrictHeight, *window, (HMENU)RESTRICT_CIRCLE, NULL, NULL);
}
