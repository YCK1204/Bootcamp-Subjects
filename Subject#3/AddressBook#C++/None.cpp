#include "None.hpp"

NoneControl* NoneControl::_instance = nullptr;

NoneControl& NoneControl::Instance() {
	if (_instance == nullptr)
		_instance = new NoneControl();
	return *_instance;
}

void NoneControl::Handle() {

}

NoneControl::NoneControl() {}