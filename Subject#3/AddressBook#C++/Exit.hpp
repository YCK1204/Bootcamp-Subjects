#ifndef EXIT_HPP
# define EXIT_HPP

#include "State.hpp"

class ExitControl : public State {
public:
	static ExitControl& Instance();
	void Handle() override;
private:
	static ExitControl* _instance;
	ExitControl();
};

#endif