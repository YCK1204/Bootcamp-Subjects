#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <vector>

#include "ContactData.hpp"

class Utils
{
public:
	static std::string ToLower(std::string str);
	static std::string Readline(std::string msg);
	static std::vector<std::string> Split(std::string& str, char delim, bool trim = false);
	static std::string Trim(std::string& str);
	static std::vector<ContactData> StringToContactData(std::string data);
	static std::string ContactDataToString(std::vector<ContactData>& data);
	static std::string ContactDataToString(ContactData& data);
	static bool CompareByNameForSort(const ContactData& a, const ContactData& b);
	static bool CompareByNumberForSort(const ContactData& a, const ContactData& b);
	static bool CompareByAddressForSort(const ContactData& a, const ContactData& b);

	static int CompareByName(const ContactData& a, const ContactData& b);
	static int CompareByNumber(const ContactData& a, const ContactData& b);
	static int CompareByAddress(const ContactData& a, const ContactData& b);
	static std::pair<size_t, size_t> SetContactRange(std::vector<ContactData> fileData, int pos, int (*func)(const ContactData&, const ContactData&), ContactData target);

#pragma region binary_search
	template <typename T>
	static int BinarySearch(std::vector<T>& arr, int start, int end, T& data, int (*func)(const T&, const T&)) {
		if (start > end)
			return -1;

		int mid = (end + start) / 2;
		int funcRet = func(arr[mid], data);
		if (funcRet == 0)
			return mid;
		else if (funcRet > 0)
			return BinarySearch(arr, start, mid - 1, data, func);
		else
			return BinarySearch(arr, mid + 1, end, data, func);
	}
#pragma endregion
};

#endif