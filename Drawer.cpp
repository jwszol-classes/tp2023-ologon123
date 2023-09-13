#include "Drawer.h"

using namespace std;
using namespace Gdiplus;

Drawer::Drawer() : context(nullptr)
{
	auto rawBlocksPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	blocksPen = std::make_shared<HPEN>(std::move(rawBlocksPen));
	auto rawCranePen = CreatePen(PS_SOLID, 4, RGB(255, 255, 0));
	cranePen = std::make_shared<HPEN>(std::move(rawCranePen));
	auto rawBlocksBrush = CreateSolidBrush(RGB(165, 42, 42));
	blocksBrush = std::make_shared<HBRUSH>(std::move(rawBlocksBrush));
	auto drawSquare = [this](int blockX, int blockY) {this->drawSquareBlock(blockX, blockY); };
	blocksDrawers.insert(pair<string, function<void(int, int)>>(string("Square"), drawSquare));
	auto drawTriangle = [this](int blockX, int blockY) {this->drawTriangleBlock(blockX, blockY); };
	blocksDrawers.insert(pair<string, function<void(int, int)>>(string("Triangle"), drawTriangle));
	auto drawCircle = [this](int blockX, int blockY) {this->drawCircleBlock(blockX, blockY); };
	blocksDrawers.insert(pair<string, function<void(int, int)>>(string("Circle"), drawCircle));
}

Drawer::~Drawer()
{
	DeleteObject(*blocksPen);
	DeleteObject(*cranePen);
	DeleteObject(*blocksBrush);
}

void Drawer::drawCrane(shared_ptr<Crane> crane)
{
	SelectPen(*context, *blocksPen);
	drawHook(crane);
	SelectPen(*context, *cranePen);
	drawHorizontalCraneElement(crane);
	drawVerticalCraneElement(crane);
}

void Drawer::drawTowers(shared_ptr<vector<shared_ptr<Tower>>> towers)
{
	SelectPen(*context, *blocksPen);
	SelectBrush(*context, *blocksBrush);
	for (auto tower: *towers)
	{
		auto blocks = tower->getBlocks();
		drawBlocks(blocks);
	}
}

void Drawer::sendContext(HDC& context)
{
	this->context = &context;
}

void Drawer::drawHorizontalCraneElement(std::shared_ptr<Crane> crane)
{
	int armLength = crane->ARM_LENGTH, basisMinX = crane->BASIS_MIN_X, basisY = crane->BASIS, width = crane->WIDTH, armMinY = crane->ARM_MIN_Y;
	int leftPoint = basisMinX - armLength / 4;
	MoveToEx(*context, leftPoint, armMinY, NULL);
	LineTo(*context, basisMinX + width + armLength, armMinY);
	MoveToEx(*context, leftPoint, basisY - 7 * armLength / 8, NULL);
	LineTo(*context, basisMinX + width + armLength, basisY - 7 * armLength / 8);
	MoveToEx(*context, leftPoint, basisY - 7 * armLength / 8, NULL);
	LineTo(*context, leftPoint, armMinY);
	MoveToEx(*context, basisMinX + width + armLength, basisY - 7 * armLength / 8, NULL);
	LineTo(*context, basisMinX + width + armLength, armMinY);
}

void Drawer::drawVerticalCraneElement(std::shared_ptr<Crane> crane)
{
	int armLength = crane->ARM_LENGTH, basisMinX = crane->BASIS_MIN_X, basisY = crane->BASIS, width = crane->WIDTH;
	int highestPoint = basisY - armLength;
	MoveToEx(*context, basisMinX, basisY, NULL);
	LineTo(*context, basisMinX, highestPoint);
	MoveToEx(*context, basisMinX + width, basisY, NULL);
	LineTo(*context, basisMinX + width, highestPoint);
	MoveToEx(*context, basisMinX, basisY, NULL);
	LineTo(*context, basisMinX + width, basisY);
	MoveToEx(*context, basisMinX, highestPoint, NULL);
	LineTo(*context, basisMinX + width, highestPoint);
}

void Drawer::drawHook(std::shared_ptr<Crane> crane)
{
	int armMinY = crane->ARM_MIN_Y, height = CraneHook::HEIGHT, width = CraneHook::WIDTH;
	int hookX = crane->getHookX(), hookY = crane->getHookY();
	MoveToEx(*context, hookX, armMinY, NULL);
	LineTo(*context, hookX, hookY + height / 2);
	MoveToEx(*context, hookX - width / 2, hookY, NULL);
	LineTo(*context, hookX + width / 2, hookY);
	auto hookedBlocks = crane->getHookedBlocks();
	drawBlocks(hookedBlocks);
}

void Drawer::drawBlocks(shared_ptr<vector<shared_ptr<Block>>> blocks)
{
	for (auto block : *blocks)
	{
		auto blockName = block->getName();
		auto blockDrawer = blocksDrawers[blockName];
		int blockX = block->getX(), blockY = block->getY();
		blockDrawer(blockX, blockY);
	}
}

void Drawer::drawSquareBlock(int blockX, int blockY)
{
	Rectangle(*context, blockX - Block::WIDTH / 2, blockY - Block::HEIGHT / 2, blockX + Block::WIDTH / 2, blockY + Block::HEIGHT / 2);
}

void Drawer::drawCircleBlock(int blockX, int blockY)
{
	Ellipse(*context, blockX - Block::WIDTH / 2, blockY - Block::HEIGHT / 2, blockX + Block::WIDTH / 2, blockY + Block::HEIGHT / 2);
}

void Drawer::drawTriangleBlock(int blockX, int blockY)
{
	POINT vertices[] = { {blockX, blockY - Block::HEIGHT / 2}, {blockX + Block::WIDTH / 2, blockY + Block::HEIGHT / 2}, {blockX - Block::WIDTH / 2, blockY + Block::HEIGHT / 2} };
	Polygon(*context, vertices, sizeof(vertices) / sizeof(vertices[0]));
}
