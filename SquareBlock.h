#pragma once
#include "Block.h"
class SquareBlock: public Block
{
public:
	SquareBlock(int x, int y, int weight);
	virtual std::string getName() override;
};

