#ifndef STATISTICSUI_HPP
# define STATISTICSUI_HPP

#include <string>
#include <list>
#include "ContactData.hpp"
#include <vector>
#include "Observer.hpp"

class StatisticsUI : public Observer {
	typedef std::vector<std::pair<int, std::string> > t_stringCntVector;
private:
	StatisticsUI();
	static StatisticsUI* _instance;
	Subject* subject;
	t_stringCntVector GetNames(std::vector<ContactData> data);
	t_stringCntVector GetAddresses(std::vector<ContactData> data);
public:
	void Update(std::vector<ContactData> data) override;
	static StatisticsUI& Instance();
};

#endif