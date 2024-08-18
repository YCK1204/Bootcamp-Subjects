#include "StaticUI.hpp"
#include <iostream>

StaticUI::StaticUI() {}

std::string StaticUI::_command =
"[EXIT] 프로그램 종료, "
"[CREATE] 주소록에 데이터 생성, "
"[READ] 조건에 맞는 데이터 출력, "
"[UPDATE] 데이터 수정, "
"[DELETE] 조건에 맞는 데이터 삭제";

std::string StaticUI::_commandSyntax = 
"Error: Command syntax error";

std::string StaticUI::_inputSyntax = 
"Error: Input syntax error";

std::string StaticUI::_dataNotFound = 
"데이터를 찾지 못했습니다.";

std::string StaticUI::_create = 
"이름, 전화번호, 주소를 입력하세요!";

std::string StaticUI::_read = 
"&와 |를 사용해 원하는 데이터를 추출하세요! \n"
"키와 값은 \'=\' 으로 구분짓습니다\n"
"사용가능한 키들 : 이름, 전화번호, 주소\n"
"ex) 이름 = 8조 & 전화번호 = 010-1234-5678 | 주소 = 서울특별시";

std::string StaticUI::_update = 
"변경 하고싶은 데이터의 전화번호를 입력하세요!";

std::string StaticUI::_delete = 
"삭제 하고싶은 데이터의 전화번호를 입력하세요!";

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