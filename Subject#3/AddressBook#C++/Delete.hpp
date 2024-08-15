#ifndef DELETE_HPP
# define DELETE_HPP

#include "State.hpp"

class DeleteControl : public State {
public:
	static DeleteControl& Instance();
	void Handle() override;
private:
	static DeleteControl* _instance;
	DeleteControl();
};

#endif