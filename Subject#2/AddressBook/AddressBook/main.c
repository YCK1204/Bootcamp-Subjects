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
		L"[EXIT] ���α׷� ����, "
		L"[CREATE] �ּҷϿ� ������ ����, "
		L"[READ] ���ǿ� �´� ������ ���, "
		L"[UPDATE] ������ ����, "
		L"[DELETE] ���ǿ� �´� ������ ����\n";

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