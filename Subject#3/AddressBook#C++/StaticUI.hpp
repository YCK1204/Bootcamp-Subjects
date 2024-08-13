#ifndef UISTATIC_HPP
# define UISTATIC_HPP
#include <string>

typedef enum {
	COMMAND,
	COMMAND_SYNTAX,
	INPUT_SYNTAX,
	DATA_NOT_FOUND,
	CREATE,
	READ,
	UPDATE,
	DELETE,
	OVERLAPPED_DATA,
	DB_EMPTY,
} UIType;

class StaticUI
{
private:
	StaticUI();
	static std::string _command;
	static std::string _commandSyntax;
	static std::string _inputSyntax;
	static std::string _dataNotFound;
	static std::string _create;
	static std::string _read;
	static std::string _update;
	static std::string _delete;
	static std::string _overlappedData;
	static std::string _dbEmpty;
public:
	static void Print(UIType type);
	std::string Readline(std::string msg);
};

#endif