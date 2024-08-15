#include "Exit.hpp"

ExitControl* ExitControl::_instance = nullptr;

ExitControl& ExitControl::Instance() {
	if (_instance == nullptr)
		_instance = new ExitControl();
	return *_instance;
}

void ExitControl::Handle() {
	::exit(0);
}

ExitControl::ExitControl() {}