#include "Manager.hpp"
#include "StaticUI.hpp"
#include "Utils.hpp"

int main(void) {
	Manager::Data.Sort();
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