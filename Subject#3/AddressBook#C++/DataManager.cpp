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

	if (total.empty() == false)
		total.erase(total.length() - 1);
	file.seekg(pos);
	return total;
}

void DataManager::UpdateData(std::string data) {
	auto pos = file.tellp();
	file.seekp(0, std::ios::end);
	if (file.tellp() > 0)
		file << '\n';
	file << data;
	file.seekp(pos);
}

void DataManager::Clear() {
	file.close();
	file.open(FILE_PATH, std::ios::in | std::ios::trunc | std::ios::out);
	if (!Instance().file.is_open() || !Instance().file.good())
	{
		std::cerr << __FILE__ << ":" << __LINE__ << " Error: can not open file";
		::exit(1);
	}
}

void DataManager::Sort() {
	std::string oldData = ToString();
	auto fileData = Utils::StringToContactData(oldData);
	std::sort(fileData.begin(), fileData.end(), Utils::CompareByNumberForSort);
	std::string newData = Utils::ContactDataToString(fileData);
	Clear();
	UpdateData(newData);
}

bool DataManager::IsEmpty() {
	auto pos = file.tellg();
	file.seekg(0, std::ios::end);
	bool empty = (file.tellg() == 0);
	file.seekg(pos);
	return empty;
}
