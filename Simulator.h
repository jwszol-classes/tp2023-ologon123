#pragma once
#include <memory>
#include <functional>
#include <string>
#include <vector>
#include "SimulatorService.h"
class Simulator
{
public:
	Simulator(std::initializer_list<std::string> createdTowerStructure);
	void setService(std::shared_ptr<SimulatorService> simulatorService);
	void launchSimulation();
private:
	void simulationIteration();
	void setOnTheFirstTower();
	void findBlock(const std::string& blockType);
	void catchBlockFromTower(std::shared_ptr<Tower> tower);
	void setOnTheLastTower();
	void returnFromTower();
	void achieveTowerBlock();
	void putBlock();

	std::shared_ptr<SimulatorService> simulatorService;
	std::shared_ptr<std::vector<std::string>> towerStructure;
};

