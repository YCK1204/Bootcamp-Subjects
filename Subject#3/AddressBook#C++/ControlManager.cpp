#include "ControlManager.hpp"
#include "StaticUI.hpp"
#include "None.hpp"
#include "Create.hpp"
#include "Read.hpp"
#include "Update.hpp"
#include "Delete.hpp"
#include "Exit.hpp"

ControlManager* ControlManager::_instance = nullptr;

ControlManager& ControlManager::Instance() {
    if (_instance == nullptr) {
        _instance = new ControlManager();
        _instance->SetState(&NoneControl::Instance());
        ReadControl::Instance();
    }
    return *_instance;
}

ControlManager::ControlManager() {
}

ControlManager::~ControlManager() {
    if (_instance != nullptr)
        delete _instance;
}

void ControlManager::SetState(State* state) {
    Instance().state = state;
}

void ControlManager::TransitionState(std::string cmd) {
    if (!cmd.compare("create")) {
        SetState(&CreateControl::Instance());
    }
    else if (!cmd.compare("read")) {
        SetState(&ReadControl::Instance());
    }
    else if (!cmd.compare("update")) {
        SetState(&UpdateControl::Instance());
    }
    else if (!cmd.compare("delete")) {
        SetState(&DeleteControl::Instance());
    }
    else if (!cmd.compare("exit")) {
        SetState(&ExitControl::Instance());
    }
    else {
        SetState(&NoneControl::Instance());
        StaticUI::Print(UIType::COMMAND_SYNTAX);
    }
}

void ControlManager::Request() {
    state->Handle();
}