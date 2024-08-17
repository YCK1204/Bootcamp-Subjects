#include "Utils.hpp"
#include <sstream>
#include <iostream>
#include <fstream>

std::string Utils::ToLower(std::string str) {
	for (size_t i = 0; str[i]; i++) {
		str[i] = std::tolower(str[i]);
	}
	return str;
}

std::string Utils::Readline(std::string msg) {
	std::string line;

	while (true) {
		std::cout << msg;
		std::getline(std::cin, line);
		line = Trim(line);
		if (!line.empty())
			break;
	}

	return line;
}

std::vector<std::string> Utils::Split(std::string& str, char delim, bool trim) {
	std::vector<std::string> ret;
	std::stringstream ss(str);

	while (!ss.eof())
	{
		std::string line;
		std::getline(ss, line, delim);
		if (trim)
			line = Trim(line);
		if (line.empty())
			continue;
		ret.push_back(line);
	}
	return ret;
}

std::string Utils::Trim(std::string& str) {
	if (str[0] == 0)
		return "";

	size_t start = 0;
	size_t end = str.length() - 1;
	while (str[start] > 0 && isspace(str[start]))
		start++;
	while (str[end] > 0 && end > start && isspace(str[end]))
		end--;
	return str.substr(start, end - start + 1);
}

std::string Utils::ContactDataToString(std::vector<ContactData>& data) {
	std::string total = "";
	int size = data.size();

	for (int i = 0; i < size; i++)
	{
		total += ContactDataToString(data[i]);
		if (i + 1 != size)
			total += "\n";
	}
	return total;
}

std::string Utils::ContactDataToString(ContactData& data) {
	std::string ret = data.GetName() + "," + data.GetNumber() + "," + data.GetAddress();
	return ret;
}

std::vector<ContactData> Utils::StringToContactData(std::string data) {
	std::vector<ContactData> ret;

	std::vector<std::string> strs = Split(data, '\n');
	for (auto str : strs) {
		std::vector<std::string> elems = Split(str, ',', true);
		ret.push_back(ContactData(elems[0], elems[1], elems[2]));
	}
	return ret;
}

bool Utils::CompareByNameForSort(const ContactData& a, const ContactData& b) {
	return a.GetName() < b.GetName();
}

bool Utils::CompareByNumberForSort(const ContactData& a, const ContactData& b) {
	return a.GetNumber() < b.GetNumber();
}

bool Utils::CompareByAddressForSort(const ContactData& a, const ContactData& b) {
	return a.GetAddress() < b.GetAddress();
}

int Utils::CompareByName(const ContactData& a, const ContactData& b) {
	return a.GetName().compare(b.GetName());
}

int Utils::CompareByNumber(const ContactData& a, const ContactData& b) {
	return a.GetNumber().compare(b.GetNumber());
}

int Utils::CompareByAddress(const ContactData& a, const ContactData& b) {
	return a.GetAddress().compare(b.GetAddress());
}

std::pair<size_t, size_t> Utils::SetContactRange(std::vector<ContactData> fileData, int pos, int (*func)(const ContactData&, const ContactData&), ContactData target) {
	int low = 0, high = pos;

	while (low <= high) {
		int mid = (low + high) / 2;
		if (func(fileData[mid], target) < 0) low = mid + 1;
		else high = mid - 1;
	}
	size_t start = low;

	low = pos;
	high = fileData.size() - 1;

	while (low <= high) {
		int mid = (low + high) / 2;
		if (func(fileData[mid], target) > 0) high = mid - 1;
		else low = mid + 1;
	}
	size_t end = high;
	return std::make_pair(start, end);
}
