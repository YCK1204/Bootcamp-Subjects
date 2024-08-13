#include "Utils.hpp"
#include <iostream>
#include <sstream>

std::string Utils::ToLower(std::string str) {
	for (size_t i = 0; str[i]; i++) {
		str[i] = std::tolower(str[i]);
	}
	return str;
}

std::string Utils::Readline(std::string msg) {
	std::cout << msg;
	std::string line;
	std::getline(std::cin, line);
	return Trim(line);
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
	while (str[start] && isspace(str[start]))
		start++;
	while (end > start && isspace(str[end]))
		end--;
	if (end <= start)
		return "";
	return str.substr(start, end - start + 1);
}