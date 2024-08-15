#ifndef READ_HPP
# define READ_HPP

#include "State.hpp"
#include <exception>
#include <vector>
#include "Utils.hpp"

class ReadControl : public State {
private:
	static ReadControl* _instance;
	ReadControl();

	void MergeAndTruncate(std::vector<ContactData>& a, std::vector<ContactData>& b);
	std::vector<ContactData> ExtractDataByAndConditions(std::string conditions, std::vector<ContactData> fileData);
	void FindCommonData(std::vector<ContactData>& a, std::vector<ContactData>& b);
	std::vector<ContactData> ExtractDataByAndConditionsHandler(std::string key, std::string value, std::vector<ContactData> fileData);
	std::vector<ContactData> ReadHandler(ContactData target, std::vector<ContactData> fileData, int (func)(const ContactData&, const ContactData&));

	class ConditionSyntaxException : public std::exception { const char* what() const throw(); };
	class DataNotFoundException : public std::exception { const char* what() const throw(); };
public:
	static ReadControl& Instance();
	void Handle() override;
};

#endif