#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <string>
#include <fstream>
#include "State.hpp"

class ControlManager
{
private:
    static ControlManager* _instance;
    State* state;
    ControlManager();
    void SetState(State* state);

public:
    static ControlManager& Instance();
    ~ControlManager();
    void TransitionState(std::string cmd);
    void Request();
};

#endif
