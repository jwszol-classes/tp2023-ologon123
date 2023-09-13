#include "CircleBlock.h"

CircleBlock::CircleBlock(int x, int y, int weight) : Block(x, y, weight)
{
}

std::string CircleBlock::getName()
{
	return "Circle";
}
