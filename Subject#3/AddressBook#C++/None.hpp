#ifndef NONE_HPP
# define NONE_HPP

#include "State.hpp"

class NoneControl : public State {
public:
	static NoneControl& Instance();
	void Handle() override;
private:
	static NoneControl* _instance;
	NoneControl();
};

#endif