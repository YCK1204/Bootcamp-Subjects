#ifndef DYNAMICUI_HPP
# define DYNAMICUI_HPP

#include <string>
#include <list>

class Observer {
public:
	virtual ~Observer() {}
	virtual void Update(std::string msg) = 0;
};

class Subject {
public:
	Subject();
	virtual ~Subject();
	virtual void Subscribe(Observer* o) = 0;
	virtual void UnSubscribe(Observer* o) = 0;
	virtual void Notify() = 0;
};

class DynamicUI : public Subject {
private:

public:
	DynamicUI();
	void Subscribe(Observer* o) override;
	void UnSubscribe(Observer* o) override;
	void Notify() override;
};

#endif