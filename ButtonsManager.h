#pragma once
#include <string>
#include <memory>
#include <windows.h>
#include "Crane.h"
#include "Simulator.h"
class ButtonsManager
{
public:
	ButtonsManager(std::shared_ptr<Crane> crane, std::shared_ptr<Simulator> simulator, std::shared_ptr<std::vector<std::string>> errorsMessages);
	void createButtons(std::shared_ptr<HWND> window);
	void handleButtonOption(int id);
private:
	void createWeightButtons(std::shared_ptr<HWND> window);
	void createControlsButtons(std::shared_ptr<HWND> window);
	void createTypesButtons(std::shared_ptr<HWND> window);

	std::shared_ptr<Crane> crane;
	std::shared_ptr<Simulator> simulator;
	std::shared_ptr<std::vector<std::string>> errorsMessages;

	const int restrictX = 25;
	const int restrictY = 450;
	const int restrictWidth = 100;
	const int restrictHeight = 25;

	const int weightX = 25;
	const int weightY = 25;
	const int weightWidth = 100;
	const int weightHeight = 25;

	const int controlsX = 25; // przyciski w okienku przesuniête
	const int controlsY = 150;
	const int controlsWidth = 75; // szerokosc przyciskow
	const int controlsHeight = 75;

	const int simulateX = 25;
	const int simulateY = 350;
	const int simulateWidth = 225;
	const int simulateHeight = 75;
};

