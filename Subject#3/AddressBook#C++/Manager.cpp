#include "Manager.hpp"
#include "StatisticsUI.hpp"

ControlManager& Manager::Control = ControlManager::Instance();
DataManager& Manager::Data = DataManager::Instance();

Manager::Manager() {}
void Manager::Init() {
	StatisticsUI::Instance();
}