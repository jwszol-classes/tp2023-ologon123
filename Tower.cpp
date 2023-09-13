#include "Tower.h"

using namespace std;

Tower::Tower(function<Block* (int, int)> blocksCreator, int numberOfBlocks, int towerX, int towerY) : towerX(towerX)
{
    blocks = shared_ptr<vector<shared_ptr<Block>>>(new vector<shared_ptr<Block>>());
    int blockX = towerX, blockY = towerY;
    for (int i = 0; i < numberOfBlocks; i++)
    {
        blocks->push_back(shared_ptr<Block>(blocksCreator(blockX, blockY))); //tworzenie bloku, nadawanie im wspó³rzêdnych
        blockY -= Block::HEIGHT;// dziêki minusowi stoj¹ na ziemii
    }
    this->towerY = blockY;
}

shared_ptr<vector<shared_ptr<Block>>> Tower::getBlocks()
{
    return blocks;
}

void Tower::removeBlock(std::shared_ptr<Block> block)
{
    int previousSize = blocks->size();
    blocks->erase(remove(blocks->begin(), blocks->end(), block), blocks->end());// przenosi bloki na konic wekytora, po czym usuwa
    if (previousSize > blocks->size())
    {
        towerY += Block::HEIGHT;
    }
}

std::shared_ptr<Block> Tower::getLastBlock()
{
    if (blocks->size() == 0)
        throw logic_error("Tower doesn't have any block.");
    return blocks->back();// jeœli nie jest pusty zwraca siê do bloku
}

void Tower::addBlock(std::shared_ptr<Block> block)
{
    if (blocks->size() == MAXIMUM_SIZE)
    {
        throw logic_error("It's not allowed to create higher tower than" + to_string(MAXIMUM_SIZE));
    }
    blocks->push_back(block);
    block->setX(towerX);
    block->setY(towerY);
    towerY -= Block::HEIGHT;
}

bool Tower::canGetBlock()
{
    return blocks->size() < MAXIMUM_SIZE;
}

int Tower::getX()
{
    return towerX;
}

int Tower::getY()
{
    return towerY;
}
