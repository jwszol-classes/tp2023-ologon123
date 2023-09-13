#include "Block.h"

Block::Block(int x, int y, int weight) : weight(weight), x(x), y(y)
{
}

int Block::getWeight()
{
    return weight;
}

int Block::getX()
{
    return x;
}

int Block::getY()
{
    return y;
}

void Block::setX(int x)
{
    this->x = x;
}

void Block::setY(int y)
{
    this->y = y;
}
