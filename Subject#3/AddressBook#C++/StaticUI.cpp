#include "StaticUI.hpp"
#include <iostream>

StaticUI::StaticUI() {}

std::string StaticUI::_command =
"[EXIT] ���α׷� ����, "
"[CREATE] �ּҷϿ� ������ ����, "
"[READ] ���ǿ� �´� ������ ���, "
"[UPDATE] ������ ����, "
"[DELETE] ���ǿ� �´� ������ ����";

std::string StaticUI::_commandSyntax = 
"Error: Command syntax error";

std::string StaticUI::_inputSyntax = 
"Error: Input syntax error";

std::string StaticUI::_dataNotFound = 
"�����͸� ã�� ���߽��ϴ�.";

std::string StaticUI::_create = 
"�̸�, ��ȭ��ȣ, �ּҸ� �Է��ϼ���!";

std::string StaticUI::_read = 
"&�� |�� ����� ���ϴ� �����͸� �����ϼ���! \n"
"Ű�� ���� \'=\' ���� ���������ϴ�\n"
"��밡���� Ű�� : �̸�, ��ȭ��ȣ, �ּ�\n"
"ex) �̸� = 8�� & ��ȭ��ȣ = 010-1234-5678 | �ּ� = ����Ư����";

std::string StaticUI::_update = 
"���� �ϰ���� �������� ��ȭ��ȣ�� �Է��ϼ���!";

std::string StaticUI::_delete = 
"���� �ϰ���� �������� ��ȭ��ȣ�� �Է��ϼ���!";

std::string StaticUI::_overlappedData = 
"Error: Record already exists.";

std::string StaticUI::_dbEmpty =
"Error: Current DB is empty.";

void StaticUI::Print(UIType type) {
	switch (type)
	{
	case COMMAND:
		std::cout << _command << std::endl;
		break;
	case COMMAND_SYNTAX:
		std::cerr << _commandSyntax << std::endl;
		break;
	case INPUT_SYNTAX:
		std::cerr << _inputSyntax << std::endl;
		break;
	case DATA_NOT_FOUND:
		std::cerr << _dataNotFound << std::endl;
		break;
	case CREATE:
		std::cout << _create << std::endl;
		break;
	case READ:
		std::cout << _read << std::endl;
		break;
	case UPDATE:
		std::cout << _update << std::endl;
		break;
	case DELETE:
		std::cout << _delete << std::endl;
		break;
	case OVERLAPPED_DATA:
		std::cerr << _overlappedData << std::endl;
		break;
	case DB_EMPTY:
		std::cerr << _dbEmpty << std::endl;
		break;
	}
}