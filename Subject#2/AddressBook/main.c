#include "FileSystem.h"
#include "MyLib.h"
#include "Utils.h"
#include "Execute.h"
#include <locale.h>
#include "Define.h"

FILE* contactsFile;
FILE* phoneBookFile;
wchar_t** CMD_HANDLER;
void (*CMD[6])(void);
size_t MAX_ID = 1;

void StartMainLoop();

int main(void) {
	Init();
	StartMainLoop();
}

void StartMainLoop() {
	wchar_t* cmd = NULL;

	wchar_t* usingGuide = 
		L"[EXIT] 프로그램 종료, "
		L"[CREATE] 주소록에 데이터 생성, "
		L"[READ] 조건에 맞는 데이터 출력, "
		L"[UPDATE] 데이터 수정, "
		L"[DELETE] 조건에 맞는 데이터 삭제\n";

	wprintf(L"%ls\n", usingGuide);
	while (true) {
		cmd = Readline(L"> ");
		if (cmd == NULL) { _OccurError(errno, __FILE__, __LINE__); }

		String_ToLower(cmd);
		ReplaceString(&cmd, Trim(cmd));
		if (MyStrcmp(cmd, L""))
			NavigateCommand(cmd);
		free(cmd);
	}
}