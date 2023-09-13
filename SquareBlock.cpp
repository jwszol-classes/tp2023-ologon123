#include "SquareBlock.h"

SquareBlock::SquareBlock(int x, int y, int weight) : Block(x, y, weight)
{
}

std::string SquareBlock::getName()
{
	return "Square";
}
