#pragma once
#include <string>
#include "HookController.h"
#include "CraneHook.h"
class Crane
{
public:
	Crane(std::shared_ptr<HookController> hookController, int maximumWeight);
	std::string getMessageAboutWeight();
	std::string getMessageAboutAllowedTypes();
	void addAllowedType(const std::string& allowedType);
	void removeAllowedType(const std::string& unallowedType);
	void switchWeightCheckerActivation();
	void hookBlock(std::shared_ptr<Block> block);
	void increaseMaximumWeight(int value);
	void decreaseMaximumWeight(int value);
	void moveHookUp();
	void moveHookDown();
	void moveHookLeft();
	void moveHookRight();
	void catchBlock();
	void dropBlock();
	std::shared_ptr<std::vector<std::shared_ptr<Block>>> getHookedBlocks();
	int getHookX();
	int getHookY();
	static const int ARM_LENGTH = 512;
	static const int BASIS = 550;
	static const int WIDTH = 50;
	static const int BASIS_MIN_X = 450;
	static const int ARM_MIN_Y = BASIS - 3 * ARM_LENGTH / 4;
private:
	std::shared_ptr<HookController> hookController;
	std::shared_ptr<CraneHook> hook;
};

