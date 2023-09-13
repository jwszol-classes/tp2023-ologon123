#include "Simulator.h"

using namespace std;

Simulator::Simulator(initializer_list<string> createdTowerStructure)
{
	towerStructure = shared_ptr<vector<string>>(new vector<string>(createdTowerStructure));
}

void Simulator::setService(std::shared_ptr<SimulatorService> simulatorService)
{
	this->simulatorService = simulatorService;
}

void Simulator::launchSimulation()
{
	simulatorService->restartWorld();
	simulatorService->showAction();
	while (towerStructure->size() > 0)
	{
		simulationIteration();
	}
}

void Simulator::simulationIteration()
{
	setOnTheFirstTower();
	findBlock(towerStructure->back());
	towerStructure->pop_back();
	setOnTheLastTower();
	putBlock();
	returnFromTower();
}

void Simulator::setOnTheFirstTower()
{
	auto crane = simulatorService->getCrane();
	try {
		while (true)
		{
			crane->moveHookLeft();
			simulatorService->showAction();
		}
	}
	catch (const exception& err)
	{
	}
}

void Simulator::findBlock(const string& blockType)
{
	auto crane = simulatorService->getCrane();
	auto towers = simulatorService->getTowers();
	for (auto tower : *towers)
	{
		try
		{
			auto towerBlock = tower->getLastBlock();
			if (towerBlock->getName() == blockType)
			{
				catchBlockFromTower(tower);
				break;
			}
		}
		catch (const std::exception&)
		{
		}
		crane->moveHookRight();
		simulatorService->showAction();
	}
}

void Simulator::catchBlockFromTower(std::shared_ptr<Tower> tower)
{
	auto crane = simulatorService->getCrane();
	achieveTowerBlock();
	crane->catchBlock();
	simulatorService->showAction();
	returnFromTower();
}

void Simulator::setOnTheLastTower()
{
	auto crane = simulatorService->getCrane();
	try {
		while (true)
		{
			crane->moveHookRight();
			simulatorService->showAction();
		}
	}
	catch (const exception& err)
	{
	}
}

void Simulator::returnFromTower()
{
	auto crane = simulatorService->getCrane();
	try
	{
		while (true)
		{
			crane->moveHookUp();
			simulatorService->showAction();
		}
	}
	catch (const std::exception&)
	{
	}
}

void Simulator::achieveTowerBlock()
{
	auto crane = simulatorService->getCrane();
	try
	{
		while (true)
		{
			crane->moveHookDown();
			simulatorService->showAction();
		}
	}
	catch (const std::exception&)
	{
	}
}

void Simulator::putBlock()
{
	auto crane = simulatorService->getCrane();
	while (true)
	{
		try
		{
			crane->moveHookDown();
			simulatorService->showAction();
			crane->dropBlock();
			simulatorService->showAction();
			break;
		}
		catch (const std::exception&)
		{
		}
	}
}
