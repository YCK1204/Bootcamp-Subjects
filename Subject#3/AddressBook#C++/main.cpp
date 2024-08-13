#include "Manager.hpp"
#include "StaticUI.hpp"
#include "Utils.hpp"
#include <iostream>


int main(void) {
	while (true)
	{
		StaticUI::Print(COMMAND);
		std::string cmd = Utils::Readline("> ");
		cmd = Utils::ToLower(cmd);
		Manager::Control.Navigate(cmd);
	}
	return 0;
}