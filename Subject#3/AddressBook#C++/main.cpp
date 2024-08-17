#include "Manager.hpp"
#include "StaticUI.hpp"
#include "Utils.hpp"
#include "StatisticsUI.hpp"
#include <algorithm>
#include <iostream>

int main(void) {
	Manager::Init();

	while (true)
	{
		StaticUI::Print(COMMAND);
		std::string cmd = Utils::Readline("> ");
		cmd = Utils::ToLower(cmd);
		Manager::Control.TransitionState(cmd);
		Manager::Control.Request();
	}
	return 0;
}