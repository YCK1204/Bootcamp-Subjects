#include "Update.hpp"
#include "StaticUI.hpp"
#include "Manager.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iostream>

UpdateControl* UpdateControl::_instance = nullptr;

UpdateControl& UpdateControl::Instance() {
	if (_instance == nullptr)
		_instance = new UpdateControl();
	return *_instance;
}

void UpdateControl::Handle() {
	if (Manager::Data.IsEmpty())
	{
		StaticUI::Print(UIType::DB_EMPTY);
		return;
	}

	StaticUI::Print(UIType::UPDATE);
	std::string nextNumber = Utils::Readline("Update > ");

	std::string fileTxt = Manager::Data.ToString();
	std::vector<ContactData> fileData = Utils::StringToContactData(fileTxt);
	std::sort(fileData.begin(), fileData.end(), Utils::CompareByNumberForSort);

	ContactData tmp;
	tmp.SetNumber(nextNumber);
	int pos = Utils::BinarySearch<ContactData>(fileData, 0, fileData.size() - 1, tmp, Utils::CompareByNumber);

	if (pos == -1)
	{
		StaticUI::Print(UIType::DATA_NOT_FOUND);
	}
	else
	{
		ContactData& data = fileData[pos];
		std::cout << "변경할 데이터를 입력해주세요!" << std::endl;

		std::string name = Utils::Readline("Update > 이름 : ");
		std::string number = Utils::Readline("Update > 전화번호 : ");
		std::string address = Utils::Readline("Update > 주소 : ");

		tmp.SetNumber(number);
		if (number.compare(data.GetNumber()) && Utils::BinarySearch(fileData, 0, fileData.size() - 1, tmp, Utils::CompareByNumber) >= 0)
		{
			StaticUI::Print(UIType::OVERLAPPED_DATA);
		}
		else
		{
			fileData[pos] = ContactData(name, number, address);
			std::string newData = Utils::ContactDataToString(fileData);
			
			Manager::Data.SetData(fileData);
			Manager::Data.Update();
		}
	}
}

UpdateControl::UpdateControl() {}