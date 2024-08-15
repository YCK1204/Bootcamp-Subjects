#ifndef UPDATE_HPP
# define UPDATE_HPP

#include "State.hpp"

class UpdateControl : public State {
public:
	static UpdateControl& Instance();
	void Handle() override;
private:
	static UpdateControl* _instance;
	UpdateControl();
};

#endif