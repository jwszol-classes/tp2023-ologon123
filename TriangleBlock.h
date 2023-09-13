#pragma once
#include "Block.h"
class TriangleBlock: public Block
{
public:
	TriangleBlock(int x, int y, int weight);
	virtual std::string getName() override;
};

