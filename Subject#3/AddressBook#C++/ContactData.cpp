#include "ContactData.hpp"

ContactData::ContactData() {}
ContactData::ContactData(std::string name, std::string number, std::string address) :
	_name(name), _number(number), _address(address) {}
ContactData::ContactData(const ContactData& data) { *this = data; }
ContactData& ContactData::operator = (const ContactData& c) {
	if (this != &c) {
		this->_name = c._name;
		this->_number = c._number;
		this->_address = c._address;
	}
	return *this;
}
std::string const ContactData::GetName() const { return _name; }
std::string const ContactData::GetNumber() const { return _number; }
std::string const ContactData::GetAddress() const { return _address; }

void ContactData::SetName(const std::string name) { _name = name; }
void ContactData::SetNumber(const std::string number) { _number = number; }
void ContactData::SetAddress(const std::string address) { _address = address; }
