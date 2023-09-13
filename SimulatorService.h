#pragma once
#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include "Crane.h"
#include "Tower.h"
class SimulatorService
{
public:
	SimulatorService(std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towers, std::shared_ptr<Crane> crane, std::function<void()> restartWorldMethod, std::function<void()> refreshGuiMethod);
	void restartWorld();
	void showAction();
	std::shared_ptr<Crane> getCrane();
	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> getTowers();
private:
	std::shared_ptr<std::vector<std::shared_ptr<Tower>>> towers;
	std::shared_ptr<Crane> crane;
	std::function<void()> restartWorldMethod;
	std::function<void()> refreshGuiMethod;
};

