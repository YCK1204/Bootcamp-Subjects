#ifndef CONTACTDATA_HPP
# define CONTACTDATA_HPP

#include <string>

class ContactData {
private:
	std::string _name;
	std::string _number;
	std::string _address;
public:
	ContactData();
	ContactData(std::string name, std::string number, std::string address);
	ContactData(const ContactData& data);
	ContactData& operator = (const ContactData& c);
	std::string const GetName() const;
	std::string const GetNumber() const;
	std::string const GetAddress() const;
	void SetName(const std::string name);
	void SetNumber(const std::string number);
	void SetAddress(const std::string address);

};

#endif