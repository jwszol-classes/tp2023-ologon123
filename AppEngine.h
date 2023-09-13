#pragma once
#include <string>
#include <memory>
#include <windows.h>
#include <gdiplus.h>
#include "Crane.h"
#include "Drawer.h"
#include "Messenger.h"
#include "ButtonsManager.h"
#include "Simulator.h"
class AppEngine
{
public:
	AppEngine();
	~AppEngine();
	void start(HINSTANCE hInstance, int nCmdShow);
	void createPaintMessage();
	void executePaint();

	std::shared_ptr<Messenger> messenger;
	std::shared_ptr<Drawer> drawer;
	std::shared_ptr<ButtonsManager> buttonsManager;
	std::shared_ptr<Crane> crane;
	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towers;
private:
	void initializeApp();
	void initializeTowers();
	void eventsLoop();
	void createWindow(HINSTANCE hInstance, int nCmdShow);

	std::map<std::string, std::function<Block* (int, int)>> blocksCreators;
	std::shared_ptr<std::vector<std::string>> errorsMessages;
	std::shared_ptr<HWND> window;
	std::shared_ptr<Simulator> simulator;
	Gdiplus::GdiplusStartupInput gdiplusParameters;
	ULONG_PTR gdiplusToken;
	const int INITIAL_WEIGHT = 150;
};

