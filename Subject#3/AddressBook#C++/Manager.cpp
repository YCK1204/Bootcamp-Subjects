#include "Manager.hpp"

ControlManager& Manager::Control = ControlManager::Instance();
DataManager& Manager::Data = DataManager::Instance();

Manager::Manager() {}