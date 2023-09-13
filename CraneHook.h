#pragma once
#include <memory>
#include <vector>
#include "ItemsWeightChecker.h"
#include "ItemsTypeChecker.h"
#include "Block.h"
class CraneHook
{
public:
	CraneHook(int x, int y, int maximumWeight);
	std::string getMessageAboutWeight();
	std::string getMessageAboutAllowedTypes();
	void addAllowedType(const std::string& allowedType);
	void removeAllowedType(const std::string& unallowedType);
	void switchWeightCheckerActivation();
	void catchBlock(std::shared_ptr<Block> block);
	void increaseMaximumWeight(int value);
	void decreaseMaximumWeight(int value);
	void moveUp(int value);
	void moveDown(int value);
	void moveLeft(int value);
	void moveRight(int value);
	bool isCarryingAnyBlock();
	int getX();
	int getY();
	std::shared_ptr<Block> dropBlock();
	std::shared_ptr<std::vector<std::shared_ptr<Block>>> getHookedBlocks();
	static const int WIDTH = Block::WIDTH;
	static const int HEIGHT = Block::HEIGHT;
private:
	void updateBlocksPosition();

	int x;
	int y;
	std::shared_ptr<ItemsWeightChecker<Block>> weightChecker;
	std::shared_ptr<ItemsTypeChecker<Block>> typeChecker;
	std::shared_ptr<std::vector<std::shared_ptr<Block>>> blocksOnHook;
};

