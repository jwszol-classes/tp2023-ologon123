#include "Crane.h"

using namespace std;

Crane::Crane(shared_ptr<HookController> hookController, int maximumWeight)
{
	int hookX = ARM_LENGTH + BASIS_MIN_X + WIDTH - CraneHook::WIDTH / 2;
	int hookY = ARM_MIN_Y + CraneHook::HEIGHT / 2;
	hook = shared_ptr<CraneHook>(new CraneHook(hookX, hookY, maximumWeight));
	this->hookController = hookController;
	hookController->setHook(hook);
}

void Crane::addAllowedType(const string& allowedType)
{
	hook->addAllowedType(allowedType);
}

void Crane::removeAllowedType(const string& unallowedType)
{
	hook->removeAllowedType(unallowedType);
}

string Crane::getMessageAboutWeight()
{
	return hook->getMessageAboutWeight();
}

string Crane::getMessageAboutAllowedTypes()
{
	return hook->getMessageAboutAllowedTypes();
}

void Crane::switchWeightCheckerActivation()
{
	hook->switchWeightCheckerActivation();
}

void Crane::hookBlock(shared_ptr<Block> block)
{
	hook->catchBlock(block);
}

void Crane::increaseMaximumWeight(int value)
{
	hook->increaseMaximumWeight(value);
}

void Crane::decreaseMaximumWeight(int value)
{
	hook->decreaseMaximumWeight(value);
}

void Crane::moveHookUp()
{
	hookController->moveUp(hook->HEIGHT, ARM_MIN_Y);
}

void Crane::moveHookDown()
{
	hookController->moveDown(hook->HEIGHT, BASIS);
}

void Crane::moveHookLeft()
{
	hookController->moveLeft(hook->WIDTH, BASIS_MIN_X + WIDTH);
}

void Crane::moveHookRight()
{
	hookController->moveRight(hook->WIDTH, BASIS_MIN_X + WIDTH + ARM_LENGTH);
}

void Crane::catchBlock()
{
	hookController->catchBlockIfPossible();
}

void Crane::dropBlock()
{
	hookController->dropBlockIfPossible();
}

shared_ptr<vector<shared_ptr<Block>>> Crane::getHookedBlocks()
{
	return hook->getHookedBlocks();
}

int Crane::getHookX()
{
	return hook->getX();
}

int Crane::getHookY()
{
	return hook->getY();
}
