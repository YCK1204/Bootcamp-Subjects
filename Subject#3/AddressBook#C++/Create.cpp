#include "Create.hpp"
#include "StaticUI.hpp"
#include "Utils.hpp"
#include "Manager.hpp"
#include <algorithm>

CreateControl* CreateControl::_instance = nullptr;

CreateControl& CreateControl::Instance() {
	if (_instance == nullptr)
		_instance = new CreateControl();
	return *_instance;
}

void CreateControl::Handle() {

	StaticUI::Print(UIType::CREATE);
	std::string name = Utils::Readline("Create > 이름 : ");
	std::string number = Utils::Readline("Create > 전화번호 : ");
	std::string addr = Utils::Readline("Create > 주소 : ");

	ContactData data(name, number, addr);

	std::string fileTxt = Manager::Data.ToString();
	std::vector<ContactData> fileData = Utils::StringToContactData(fileTxt);

	int pos = -1;

	if (fileData.size() > 0) {
		std::sort(fileData.begin(), fileData.end(), Utils::CompareByNumberForSort);
		pos = Utils::BinarySearch<ContactData>(fileData, 0, fileData.size() - 1, data, Utils::CompareByNumber);
	}
	if (pos >= 0) {
		StaticUI::Print(UIType::OVERLAPPED_DATA);
		return;
	}
	fileData.push_back(ContactData(name, number, addr));
	Manager::Data.SetData(fileData);
	Manager::Data.Update();
}

CreateControl::CreateControl() {}