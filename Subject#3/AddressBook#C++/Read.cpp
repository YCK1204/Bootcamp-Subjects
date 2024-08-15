#include "Read.hpp"
#include "Manager.hpp"
#include "StaticUI.hpp"
#include "Utils.hpp"
#include <iostream>
#include <algorithm>

ReadControl* ReadControl::_instance = nullptr;

ReadControl& ReadControl::Instance() {
	if (_instance == nullptr)
		_instance = new ReadControl();
	return *_instance;
}

std::vector<ContactData> ReadControl::ReadHandler(ContactData target, std::vector<ContactData> fileData, int (func)(const ContactData&, const ContactData&))
{
	std::vector<ContactData> ret;

	int pos = Utils::BinarySearch<ContactData>(fileData, 0, fileData.size() - 1, target, func);
	if (pos >= 0)
	{
		std::pair<size_t, size_t> bondaryPos = Utils::SetContactRange(fileData, pos, func, target);
		for (size_t i = bondaryPos.first; i <= bondaryPos.second; i++)
			ret.push_back(ContactData(fileData[i]));
	}
	else {
		throw DataNotFoundException();
	}
	return ret;
}

std::vector<ContactData> ReadControl::ExtractDataByAndConditionsHandler(std::string key, std::string value, std::vector<ContactData> fileData)
{
	ContactData tmpData(value, value, value);

	if (!key.compare("이름")) {
		std::sort(fileData.begin(), fileData.end(), Utils::CompareByNameForSort);
		return ReadHandler(tmpData, fileData, Utils::CompareByName);
	}
	else if (!key.compare("전화번호")) {
		std::sort(fileData.begin(), fileData.end(), Utils::CompareByNumberForSort);
		return ReadHandler(tmpData, fileData, Utils::CompareByNumber);
	}
	else if (!key.compare("주소")) {
		std::sort(fileData.begin(), fileData.end(), Utils::CompareByAddressForSort);
		return ReadHandler(tmpData, fileData, Utils::CompareByAddress);
	}
	throw ConditionSyntaxException();
}

void ReadControl::FindCommonData(std::vector<ContactData>& a, std::vector<ContactData>& b)
{
	std::vector<ContactData> tmp;
	if (a.size() == 0)
	{
		for (auto Bdata : b)
			a.push_back(ContactData(Bdata));
	}
	else
	{
		std::sort(b.begin(), b.end(), Utils::CompareByNumberForSort);

		for (int i = 0; i < a.size(); i++) {

			if (i > 0 && Utils::CompareByNumber(a[i - 1], a[i]) == 0)
				continue;
			if (Utils::BinarySearch<ContactData>(b, 0, b.size() - 1, a[i], Utils::CompareByNumber) >= 0) {
				tmp.push_back(a[i]);
				continue;
			}
		}
		a.clear();
		for (auto s : tmp) {
			a.push_back(s);
		}
	}
}

std::vector<ContactData> ReadControl::ExtractDataByAndConditions(std::string conditions, std::vector<ContactData> fileData)
{
	std::vector<ContactData> ret;

	std::vector<std::string> andConditions = Utils::Split(conditions, '&', true);
	for (auto condition : andConditions) {
		std::vector<std::string> keyAndValue = Utils::Split(condition, '=', true);

		if (keyAndValue.size() != 2)
			throw ConditionSyntaxException();

		// 알맞게 파싱된 경우
		std::string key = keyAndValue[0];
		std::string value = keyAndValue[1];
		std::vector<ContactData> data = ExtractDataByAndConditionsHandler(key, value, fileData);

		// data를 찾은 경우
		if (data.size() > 0)
			FindCommonData(ret, data);
	}
	return ret;
}

void ReadControl::MergeAndTruncate(std::vector<ContactData>& a, std::vector<ContactData>& b)
{
	if (a.size() == 0)
	{
		for (auto Bdata : b)
			a.push_back(Bdata);
	}
	else
	{
		std::sort(a.begin(), a.end(), Utils::CompareByNumberForSort);

		for (auto Bdata : b) {
			if (Utils::BinarySearch<ContactData>(a, 0, a.size() - 1, Bdata, Utils::CompareByNumber) >= 0)
				continue;
			a.push_back(ContactData(Bdata));
		}
	}
}

void ReadControl::Handle() {
	if (Manager::Data.IsEmpty())
	{
		StaticUI::Print(UIType::DB_EMPTY);
		return;
	}

	StaticUI::Print(UIType::READ);
	std::string conditions = Utils::Readline("Read > ");
	std::vector<std::string> orConditions = Utils::Split(conditions, '|', true);

	std::string fileTxt = Manager::Data.ToString();
	std::vector<ContactData> fileData = Utils::StringToContactData(fileTxt);
	std::vector<ContactData> resultData;

	try
	{
		for (auto condition : orConditions) {
			std::vector<ContactData> data = ExtractDataByAndConditions(condition, fileData);
			MergeAndTruncate(resultData, data);
		}
		if (resultData.size() == 0) {
			StaticUI::Print(UIType::DATA_NOT_FOUND);
		}
		else {
			std::sort(resultData.begin(), resultData.end(), Utils::CompareByNameAndNumberForSort);
			for (auto data : resultData) {
				std::cout << data.GetName() + "," + data.GetNumber() + "," + data.GetAddress() << std::endl;
			}
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

ReadControl::ReadControl() {}
const char* ReadControl::ConditionSyntaxException::what() const throw() { return "Error: Condition Syntax is not valid"; }
const char* ReadControl::DataNotFoundException::what() const throw() { return "Error: Data Not Found"; }