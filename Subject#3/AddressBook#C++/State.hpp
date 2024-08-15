#ifndef STATE_HPP
# define STATE_HPP

#include <fstream>

class State {
public:
	virtual ~State() = default;
	virtual void Handle() = 0;
};

#endif