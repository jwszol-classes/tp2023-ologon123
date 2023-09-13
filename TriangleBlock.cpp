#include "TriangleBlock.h"

TriangleBlock::TriangleBlock(int x, int y, int weight) : Block(x, y, weight)
{
}

std::string TriangleBlock::getName()
{
    return "Triangle";
}
