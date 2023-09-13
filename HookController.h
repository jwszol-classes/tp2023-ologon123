#pragma once
#include <stdexcept>
#include "CraneHook.h"
#include "Tower.h"
class HookController
{
public:
	HookController(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towers);
	void setHook(std::shared_ptr<CraneHook> hook);
	void moveUp(int value, int limit);
	void moveDown(int value, int limit);
	void moveLeft(int value, int limit);
	void moveRight(int value, int limit);
	void catchBlockIfPossible();
	void dropBlockIfPossible();
private:
	bool willHookCollideWithBlock(int newHookX, int newHookY);
	bool isHookCollidingWithBlock();
	std::shared_ptr<Block> getCollidingBlock();
	
	std::shared_ptr<CraneHook> hook;
	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towers;
};

