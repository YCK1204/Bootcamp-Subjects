#ifndef UTILS_HPP
# define UTILS_HPP

#include <string>
#include <vector>

class Utils
{
public:
	static std::string ToLower(std::string str);
	static std::string Readline(std::string msg);
	static std::vector<std::string> Split(std::string& str, char delim, bool trim = false);
	static std::string Trim(std::string& str);
};

#endif