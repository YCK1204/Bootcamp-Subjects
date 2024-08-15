#ifndef CREATE_HPP
# define CREATE_HPP

#include "State.hpp"

class CreateControl : public State {
public:
	static CreateControl& Instance();
	void Handle() override;
private:
	static CreateControl* _instance;
	CreateControl();
};

#endif