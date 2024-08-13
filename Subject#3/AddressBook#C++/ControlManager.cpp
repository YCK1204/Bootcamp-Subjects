#include "ControlManager.hpp"
#include "StaticUI.hpp"

ControlManager* ControlManager::_instance = nullptr;

void ControlManager::Navigate(const std::string& cmd) {
    auto it = this->cmd.find(cmd);
    if (it == this->cmd.end()) {
        StaticUI::Print(UIType::COMMAND_SYNTAX);
        return;
    }
    it->second();
}

ControlManager& ControlManager::Instance() {
    if (_instance == nullptr) {
        _instance = new ControlManager();
    }
    return *_instance;
}

ControlManager::ControlManager() {
    Init();
}

ControlManager::~ControlManager() {
}

void ControlManager::Init() {
    cmd["create"] = std::bind(&ControlManager::Create, this);
    cmd["read"] = std::bind(&ControlManager::Read, this);
    cmd["update"] = std::bind(&ControlManager::Update, this);
    cmd["delete"] = std::bind(&ControlManager::Delete, this);
    cmd["exit"] = std::bind(&ControlManager::Exit, this);
}

void ControlManager::Create() {
    StaticUI::Print(UIType::CREATE);
}

void ControlManager::Read() {
    StaticUI::Print(UIType::READ);
}

void ControlManager::Update() {
    StaticUI::Print(UIType::UPDATE);
}

void ControlManager::Delete() {
    StaticUI::Print(UIType::DELETE);
}

void ControlManager::Exit() {
    ::exit(0);
}