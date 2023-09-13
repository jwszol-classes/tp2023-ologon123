#pragma once
#include "Block.h"
class CircleBlock : public Block
{
public:
	CircleBlock(int x, int y, int weight);
	virtual std::string getName() override;
};

