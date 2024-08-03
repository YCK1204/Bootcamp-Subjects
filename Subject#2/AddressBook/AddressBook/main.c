#include "FileSystem.h"
#include "MyLib.h"
#include "Utils.h"
#include "Execute.h"
#include "Define.h"

wchar_t** CMD_HANDLER;
void (*CMD[6])(void);
FILE* contactsFile;
wchar_t** READ_HANDER;

void StartMainLoop();

int main(void) {
	Init();
	StartMainLoop();
	return 0;
}

void StartMainLoop() {
	wchar_t* usingGuide =
		L"[EXIT] 프로그램 종료, "
		L"[CREATE] 주소록에 데이터 생성, "
		L"[READ] 조건에 맞는 데이터 출력, "
		L"[UPDATE] 데이터 수정, "
		L"[DELETE] 조건에 맞는 데이터 삭제\n";

	wprintf(L"%ls\n", usingGuide);
	while (true) {
		wchar_t* cmd = Readline(L"> ");
		if (cmd == NULL) { _OccurError(errno, __FILE__, __LINE__); }

		String_ToLower(cmd);
		if (MyStrcmp(cmd, L"exit") == 0)
			break;
		NavigateCommand(cmd);
		free(cmd);
	}
}