#include "DataManager.hpp"
#include <iostream>
#include "Utils.hpp"
#include <algorithm>

DataManager* DataManager::_instance = nullptr;

DataManager::DataManager() {}

DataManager::~DataManager() {
	if (_instance != nullptr) {
		file.close();
		delete _instance;
	}
}

DataManager& DataManager::Instance() {
	if (_instance == nullptr) {
		_instance = new DataManager();
		Instance().file.open(FILE_PATH, std::ios::in | std::ios::out);
		if (!Instance().file.is_open() || !Instance().file.good())
		{
			std::cerr << __FILE__ << ":" << __LINE__ << " Error: can not open file";
			::exit(1);
		}
	}
	return *_instance;
}

std::string DataManager::ToString() {
	auto pos = file.tellg();
	file.seekg(0);
	std::string total = "";

	std::string line;
	while (!file.eof()) {
		std::getline(file, line);
		total += line;
		if (!file.eof())
			total += "\n";
	}
	
	file.seekg(pos);
	return total;
}

void DataManager::Update() {
	Clear();
	std::string txt = Utils::ContactDataToString(data);
	file << txt;
}

void DataManager::Clear() {
	file.close();
	file.open(FILE_PATH, std::ios::in | std::ios::trunc | std::ios::out);
	if (!file.is_open() || !file.good())
	{
		std::cerr << __FILE__ << ":" << __LINE__ << " Error: can not open file";
		::exit(1);
	}
}

void DataManager::Sort() {
	std::string oldData = ToString();
	auto fileData = Utils::StringToContactData(oldData);
	std::sort(fileData.begin(), fileData.end(), Utils::CompareByNumberForSort);
	data = fileData;
	Clear();
	Update();
}

bool DataManager::IsEmpty() {
	auto pos = file.tellg();
	file.seekg(0, std::ios::end);
	bool empty = (file.tellg() == 0);
	file.seekg(pos);
	return empty;
}

void DataManager::Subscribe(Observer* o) {
	_observers.push_back(o);
}

void DataManager::UnSubscribe(Observer* o) {
	_observers.remove(o);
}

void DataManager::Notify() const {
	for (auto o : _observers) {
		o->Update(data);
	}
}

void DataManager::SetData(std::vector<ContactData>& data, bool notify) {
	this->data = data;
	if (notify)
		Notify();
}