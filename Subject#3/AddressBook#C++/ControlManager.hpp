#ifndef CONTROL_HPP
#define CONTROL_HPP

#include <string>
#include <fstream>
#include <map>
#include <functional>
#include <iostream>

class ControlManager
{
private:
    static ControlManager* _instance;
    ControlManager();
    std::map<std::string, std::function<void()>> cmd;
    void Init();
    void Create();
    void Read();
    void Update();
    void Delete();
    void Exit();

public:
    static ControlManager& Instance();
    ~ControlManager();
    void Navigate(const std::string& cmd);
};

#endif
