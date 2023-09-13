#include "SimulatorService.h"
#define DELAY 0.05s

using namespace std;
using namespace chrono_literals;

SimulatorService::SimulatorService(shared_ptr<vector<shared_ptr<Tower>>> towers, shared_ptr<Crane> crane,
	function<void()> restartWorldMethod, function<void()> refreshGuiMethod) : restartWorldMethod(restartWorldMethod), refreshGuiMethod(refreshGuiMethod)
{
	this->towers = towers;
	this->crane = crane;
}

void SimulatorService::restartWorld()
{
	restartWorldMethod();
}

void SimulatorService::showAction()
{
	refreshGuiMethod();
	this_thread::sleep_for(DELAY);
}

shared_ptr<Crane> SimulatorService::getCrane()
{
	return crane;
}

shared_ptr<vector<shared_ptr<Tower>>> SimulatorService::getTowers()
{
	return towers;
}
