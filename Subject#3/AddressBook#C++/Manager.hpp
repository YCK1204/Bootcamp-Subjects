#ifndef MANAGER_HPP
# define MANAGER_HPP

#include "ControlManager.hpp"
#include "DataManager.hpp"
#include "AddressBookManager.hpp"

class Manager
{
private:
	Manager();

public:
	static ControlManager& Control;
	static DataManager& Data;
	static AddressBookManager& AddressBook;
};

#endif