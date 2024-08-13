#include "DataManager.hpp"

DataManager* DataManager::_instance = nullptr;

DataManager::DataManager() {}

DataManager& DataManager::Instance() {
	if (_instance == nullptr)
		_instance = new DataManager();
	return *_instance;
}

DataManager::~DataManager() {
	delete _instance;
}

void DataManager::Init() {}
