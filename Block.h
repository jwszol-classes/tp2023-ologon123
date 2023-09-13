#pragma once
#include <string>
class Block
{
public:
	Block(int x, int y, int weight);
	int getWeight();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	virtual std::string getName() = 0;

	static const int HEIGHT = 64;
	static const int WIDTH = 64;
private:
	int weight;
	int x;
	int y;
};

