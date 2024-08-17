#ifndef OBSERVER_HPP
# define OBSERVER_HPP

#include <list>
#include "ContactData.hpp"
#include <vector>

class Observer {
public:
	virtual ~Observer() {}
	virtual void Update(std::vector<ContactData> data) = 0;
};

class Subject {
protected:
	std::list<Observer*> _observers;

public:
	virtual ~Subject() {}
	virtual void Subscribe(Observer* o) = 0;
	virtual void UnSubscribe(Observer* o) = 0;
	virtual void Notify() const = 0;
};
#endif