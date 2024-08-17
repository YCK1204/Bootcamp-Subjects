#include "StatisticsUI.hpp"
#include <iostream>
#include "Manager.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iomanip> 

StatisticsUI* StatisticsUI::_instance = nullptr;

StatisticsUI::StatisticsUI() {}

StatisticsUI& StatisticsUI::Instance() {
	if (_instance == nullptr) {
		_instance = new StatisticsUI();
		Instance().subject = &Manager::Data.Instance();
		Instance().subject->Subscribe(&Instance());
	}
	return *_instance;
}

typedef std::vector<std::pair<int, std::string> > t_stringCntVector;

t_stringCntVector StatisticsUI::GetNames(std::vector<ContactData> data) {
	t_stringCntVector ret;

	std::sort(data.begin(), data.end(), Utils::CompareByNameForSort);

	for (size_t i = 0; i < data.size(); i++) {
		std::pair<int, int> boundaryPos = Utils::SetContactRange(data, i, Utils::CompareByName, data[i]);
		int size = boundaryPos.second - boundaryPos.first + 1;
		ret.push_back(std::make_pair(size, data[i].GetName()));
		i = boundaryPos.second;
	}
	return ret;
}

t_stringCntVector StatisticsUI::GetAddresses(std::vector<ContactData> data) {
	t_stringCntVector ret;

	std::sort(data.begin(), data.end(), Utils::CompareByAddressForSort);

	for (size_t i = 0; i < data.size(); i++) {
		std::pair<int, int> boundaryPos = Utils::SetContactRange(data, i, Utils::CompareByAddress, data[i]);
		int size = boundaryPos.second - boundaryPos.first + 1;
		ret.push_back(std::make_pair(size, data[i].GetAddress()));
		i = boundaryPos.second;
	}
	return ret;
}
void StatisticsUI::Display(std::vector<ContactData> data) {
	auto namesCnt = GetNames(data);
	auto addressesCnt = GetAddresses(data);
	size_t size = data.size();
	float onePOfSize = size / (float)100;
	size_t alignSize = 30;

	std::cout << "데이터 총 개수 : " << data.size() << std::endl;
	std::cout
		<< std::setw(alignSize) << std::setfill(' ') << std::left
		<< "이름|"
		<< std::setw(10) << std::setfill(' ')
		<< "레코드 수|"
		<< std::setw(alignSize) << std::setfill(' ')
		<< "비율"
		<< std::endl;
	for (auto nameCnt : namesCnt) {
		std::cout << std::fixed;
		std::cout.precision(2);
		std::cout
			<< std::setw(alignSize) << std::setfill(' ') << std::left
			<< nameCnt.second << "|"
			<< std::setw(10) << std::setfill(' ')
			<< nameCnt.first << "|"
			<< std::to_string((float)nameCnt.first / onePOfSize) + "%"
			<< std::endl;
	}
	std::cout << std::endl;
	std::cout << "주소, 레코드 수, 비율" << std::endl;
	for (auto addressCnt : addressesCnt) {
		std::cout << std::fixed;
		std::cout.precision(2);
		std::cout
			<< std::setw(alignSize) << std::setfill(' ') << std::left
			<< addressCnt.second << "|"
			<< std::setw(10) << std::setfill(' ')
			<< addressCnt.first << "|"
			<< std::to_string((float)addressCnt.first / onePOfSize) + "%"
			<< std::endl;
	}
	std::cout << std::endl;
}

void StatisticsUI::Update(std::vector<ContactData> data) {
	std::cout << "통계화면을 보시겠습니까? Yes or No(Y/N)을 입력해주세요" << std::endl;
	std::string userInput = Utils::Readline("> ");
	userInput = Utils::ToLower(userInput);
	if (userInput.compare("yes") && userInput.compare("y"))
		return;
}
