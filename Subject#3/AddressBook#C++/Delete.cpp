#include "Delete.hpp"
#include "StaticUI.hpp"
#include "Manager.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iostream>

DeleteControl* DeleteControl::_instance = nullptr;

DeleteControl& DeleteControl::Instance() {
	if (_instance == nullptr)
		_instance = new DeleteControl();
	return *_instance;
}

void DeleteControl::Handle() {
	if (Manager::Data.IsEmpty()) {
		StaticUI::Print(UIType::DB_EMPTY);
		return;
	}

	std::cout << "삭제 하고싶은 데이터의 전화번호를 입력하세요!" << std::endl;
	std::string delNumber = Utils::Readline("Delete > ");

	std::string fileTxt = Manager::Data.ToString();
	auto fileData = Utils::StringToContactData(fileTxt);
	
	std::sort(fileData.begin(), fileData.end(), Utils::CompareByNumberForSort);

	ContactData tmp;
	tmp.SetNumber(delNumber);
	int pos = Utils::BinarySearch(fileData, 0, fileData.size() - 1, tmp, Utils::CompareByNumber);

	if (pos == -1)
	{
		StaticUI::Print(UIType::DATA_NOT_FOUND);
	}
	else
	{
		fileData.erase(fileData.begin() + pos);
		std::string newData = Utils::ContactDataToString(fileData);
		Manager::Data.Clear();
		Manager::Data.UpdateData(newData);
	}
}

DeleteControl::DeleteControl() {}