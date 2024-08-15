#ifndef DATA_HPP
# define DATA_HPP

#include <fstream>
#include <string>
#define FILE_PATH "contacts.csv"

class DataManager
{
private:
	static DataManager* _instance;
	std::fstream file;
	DataManager();
public:
	static DataManager& Instance();
	void UpdateData(std::string data);
	void Clear();
	void Sort();
	std::string ToString();
	bool IsEmpty();
	~DataManager();
};

#endif