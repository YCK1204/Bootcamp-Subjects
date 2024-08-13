#include "Manager.hpp"

ControlManager& Manager::Control = ControlManager::Instance();
AddressBookManager& Manager::AddressBook = AddressBookManager::Instance();
DataManager& Manager::Data = DataManager::Instance();


Manager::Manager() {}