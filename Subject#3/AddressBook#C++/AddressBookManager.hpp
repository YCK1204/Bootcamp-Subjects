#ifndef ADDRESSBOOK_HPP
# define ADDRESSBOOK_HPP

#include <fstream>

#define FILE_PATH "contacts.csv"

class AddressBookManager {
private:
	std::fstream file;
	static AddressBookManager* _instance;
	AddressBookManager();
public:
	static AddressBookManager& Instance();
	~AddressBookManager();
};

#endif