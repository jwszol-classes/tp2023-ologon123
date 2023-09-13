#include <stdexcept>
#include "CraneHook.h"

using namespace std;

CraneHook::CraneHook(int x, int y, int maximumWeight) : x(x), y(y)
{
	weightChecker = shared_ptr<ItemsWeightChecker<Block>>(new ItemsWeightChecker<Block>(maximumWeight));
	typeChecker = shared_ptr<ItemsTypeChecker<Block>>(new ItemsTypeChecker<Block>({"Square", "Circle", "Triangle"}));
	blocksOnHook = shared_ptr<vector<shared_ptr<Block>>>(new vector<shared_ptr<Block>>());
}

string CraneHook::getMessageAboutWeight()
{
	return weightChecker->getMessageAboutWeight(blocksOnHook);
}

void CraneHook::addAllowedType(const string& allowedType)
{
	typeChecker->addAllowedType(allowedType);
}

void CraneHook::removeAllowedType(const string& unallowedType)
{
	typeChecker->removeAllowedType(unallowedType);
}

string CraneHook::getMessageAboutAllowedTypes()
{
	return typeChecker->getMessageAboutAllowedTypes();
}

void CraneHook::switchWeightCheckerActivation()
{
	weightChecker->changeActivation();
}

void CraneHook::catchBlock(shared_ptr<Block> block)
{
	if (!weightChecker->allowsToCarryNewItem(blocksOnHook, block))
	{
		string errorMessage = "It's not possible to hook the block because it's weight is too big.";
		throw logic_error(errorMessage);
	}
	if (!typeChecker->allowsToCarryNewItem(blocksOnHook, block))
	{
		string errorMessage = "It's not possible to hook the block because it's not allowed.";
		throw logic_error(errorMessage);
	}
	blocksOnHook->push_back(block);
	updateBlocksPosition();
}

std::shared_ptr<Block> CraneHook::dropBlock()
{
	if (blocksOnHook->size() == 0)
	{
		throw logic_error("Hook isn't carrying any block!");
	}
	auto block = blocksOnHook->back();
	blocksOnHook->pop_back();
	updateBlocksPosition();
	return block;
}

void CraneHook::increaseMaximumWeight(int value)
{
	weightChecker->increaseMaximumWeight(value);
}

void CraneHook::decreaseMaximumWeight(int value)
{
	weightChecker->decreaseMaximumWeight(value);
}

void CraneHook::moveUp(int value)
{
	y -= value;
	updateBlocksPosition();
}

void CraneHook::moveDown(int value)
{
	y += value;
	updateBlocksPosition();
}

void CraneHook::moveLeft(int value)
{
	x -= value;
	updateBlocksPosition();
}

void CraneHook::moveRight(int value)
{
	x += value;
	updateBlocksPosition();
}

bool CraneHook::isCarryingAnyBlock()
{
	return blocksOnHook->size() > 0;
}

shared_ptr<vector<shared_ptr<Block>>> CraneHook::getHookedBlocks()
{
	return blocksOnHook;
}

int CraneHook::getX()
{
	return x;
}

int CraneHook::getY()
{
	return y;
}

void CraneHook::updateBlocksPosition()
{
	int diff = Block::HEIGHT, blockY = y - diff * blocksOnHook->size();
	for (auto block : *blocksOnHook)
	{
		block->setX(x);
		block->setY(blockY);
		blockY += diff;
	}
}
