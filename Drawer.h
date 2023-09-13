#pragma once
#include <string>
#include <map>
#include <functional>
#include <Windows.h>
#include <Windowsx.h>
#include <Gdiplus.h>
#include "Crane.h"
#include "Tower.h"
class Drawer
{
public:
	Drawer();
	~Drawer();
	void drawCrane(std::shared_ptr<Crane> crane);
	void drawTowers(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towers);
	void sendContext(HDC& context);
private:
	void drawHorizontalCraneElement(std::shared_ptr<Crane> crane);
	void drawVerticalCraneElement(std::shared_ptr<Crane> crane);
	void drawHook(std::shared_ptr<Crane> crane);
	void drawBlocks(std::shared_ptr<std::vector<std::shared_ptr<Block>>> blocks);
	void drawSquareBlock(int blockX, int blockY);
	void drawCircleBlock(int blockX, int blockY);
	void drawTriangleBlock(int blockX, int blockY);

	std::map<std::string, std::function<void(int, int)>> blocksDrawers;
	std::shared_ptr<HPEN> blocksPen;
	std::shared_ptr<HPEN> cranePen;
	std::shared_ptr<HBRUSH> blocksBrush;
	HDC* context;
};

