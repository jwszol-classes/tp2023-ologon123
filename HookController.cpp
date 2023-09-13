#include "HookController.h"

using namespace std;

HookController::HookController(shared_ptr<vector<shared_ptr<Tower>>> towers)
{
	this->towers = towers;
}

void HookController::setHook(shared_ptr<CraneHook> hook)
{
	this->hook = hook;
}

void HookController::moveUp(int value, int limit)
{
	int newValue = hook->getY() - value;
	if (newValue < limit)
	{
		throw logic_error("Hook can't move up");
	}
	hook->moveUp(value);
}

void HookController::moveDown(int value, int limit)
{
	int newValue = hook->getY() + value;
	if (newValue > limit)
	{
		throw logic_error("Hook can't move down");
	}
	if (isHookCollidingWithBlock())
	{
		throw logic_error("Hook can't move down into the block");
	}
	hook->moveDown(value);
}

void HookController::moveLeft(int value, int limit)
{
	int newValue = hook->getX() - value;
	if (newValue < limit)
	{
		throw logic_error("Hook can't move left");
	}
	if (willHookCollideWithBlock(newValue, hook->getY()))
	{
		throw logic_error("Hook can't move left into the block");
	}
	if (isHookCollidingWithBlock())
	{
		throw logic_error("Hook can't move left from the block");
	}
	hook->moveLeft(value);
}

void HookController::moveRight(int value, int limit)
{
	int newValue = hook->getX() + value;
	if (newValue > limit)
	{
		throw logic_error("Hook can't move right");
	}
	if (willHookCollideWithBlock(newValue, hook->getY()))
	{
		throw logic_error("Hook can't move right into the block");
	}
	if (isHookCollidingWithBlock())
	{
		throw logic_error("Hook can't move right from the block");
	}
	hook->moveRight(value);
}

void HookController::catchBlockIfPossible()
{
	auto block = getCollidingBlock();
	hook->catchBlock(block);
	for (auto tower : *towers)
	{
		tower->removeBlock(block);
	}
}

void HookController::dropBlockIfPossible()
{
	if (!hook->isCarryingAnyBlock())
	{
		throw logic_error("Hook isn't carrying any block!");
	}
	for (auto tower : *towers)
	{
		if (tower->getX() == hook->getX() && tower->getY() == hook->getY())
		{
			if (!tower->canGetBlock())
			{
				throw logic_error("It's not allowed to create higher tower than " + to_string(Tower::MAXIMUM_SIZE));
			}
			auto block = hook->dropBlock();
			tower->addBlock(block);
			return;
		}
	}
	throw logic_error("Block should be dropped in proper place");
}

bool HookController::willHookCollideWithBlock(int newHookX, int newHookY)
{
	for (auto tower: *towers)
	{
		auto blocks = tower->getBlocks();
		for (auto block : *blocks)
		{
			if (block->getX() == newHookX && block->getY() == newHookY)
			{
				return true;
			}
		}
	}
	return false;
}

bool HookController::isHookCollidingWithBlock()
{
	return willHookCollideWithBlock(hook->getX(), hook->getY());
}

shared_ptr<Block> HookController::getCollidingBlock()
{
	for (auto tower : *towers)
	{
		auto blocks = tower->getBlocks();
		for (auto block : *blocks)
		{
			if (block->getX() == hook->getX() && block->getY() == hook->getY())
			{
				return block;
			}
		}
	}
	throw logic_error("There is no colliding block");
}
