#include "AddressBookManager.hpp"
#include <iostream>

AddressBookManager* AddressBookManager::_instance = nullptr;

AddressBookManager::AddressBookManager() {}
AddressBookManager& AddressBookManager::Instance() {
	if (_instance == nullptr) {
		_instance = new AddressBookManager();
		Instance().file.open(FILE_PATH, std::ios::in | std::ios::out);
		if (Instance().file.is_open() == false)
		{
			std::cerr << __FILE__ << ":" << __LINE__ << " Error: can not open file";
			::exit(1);
		}
	}
	return *_instance;
}

AddressBookManager::~AddressBookManager() {
	file.close();
	delete _instance;
}