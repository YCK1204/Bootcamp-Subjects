#ifndef DATA_HPP
# define DATA_HPP

#include <fstream>
#include <string>
#define FILE_PATH "contacts.csv"

#include "Observer.hpp"

class DataManager : public Subject
{
private:
	static DataManager* _instance;
	std::vector<ContactData> data;
	std::fstream file;
	DataManager();
public:
	static DataManager& Instance();
	void Update();
	void Clear();
	void Sort();
	void Subscribe(Observer* o) override;
	void UnSubscribe(Observer* o) override;
	void Notify() const override;
	void SetData(std::vector<ContactData>& data, bool notify = true);
	std::string ToString();
	bool IsEmpty();
	~DataManager();
};

#endif