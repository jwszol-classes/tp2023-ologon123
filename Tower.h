#pragma once
#include <stdexcept>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include "Block.h"
class Tower
{
public:
	Tower(std::function<Block* (int, int)> blocksCreator, int numberOfBlocks, int towerX, int towerY);
	std::shared_ptr<std::vector<std::shared_ptr<Block>>> getBlocks();
	void removeBlock(std::shared_ptr<Block> block);
	std::shared_ptr<Block> getLastBlock();
	void addBlock(std::shared_ptr<Block> block);
	bool canGetBlock();
	int getX();
	int getY();
	static const int MAXIMUM_SIZE = 3;
private:
	std::shared_ptr<std::vector<std::shared_ptr<Block>>> blocks;
	int towerX;
	int towerY;
};

