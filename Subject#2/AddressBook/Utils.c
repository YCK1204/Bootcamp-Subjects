#include "Utils.h"
#include "FileSystem.h"
#include "Execute.h"
#include "MyLib.h"

void Init() {
	setlocale(LC_ALL, ".UTF-8");

	if (fopen_s(&contactsFile, CONTACTS_PATH, "r+, ccs=UNICODE") != 0) {
		if (fopen_s(&contactsFile, CONTACTS_PATH, "w+, ccs=UNICODE") != 0)
			_OccurError(errno, __FILE__, __LINE__);
	}
	CMD_HANDLER = (wchar_t**)malloc(sizeof(wchar_t*) * 6);
	CMD_HANDLER[0] = _wcsdup(L"create");
	CMD_HANDLER[1] = _wcsdup(L"read");
	CMD_HANDLER[2] = _wcsdup(L"update");
	CMD_HANDLER[3] = _wcsdup(L"delete");
	CMD_HANDLER[4] = _wcsdup(L"exit");
	CMD_HANDLER[5] = NULL;

	CMD[0] = Create;
	CMD[1] = Read;
	CMD[2] = Update;
	CMD[3] = Delete;
	CMD[4] = Exit;
	CMD[5] = None;

	READ_HANDER = (wchar_t**)malloc(sizeof(wchar_t*) * 3);
	READ_HANDER[0] = _wcsdup(L"이름");
	READ_HANDER[1] = _wcsdup(L"전화번호");
	READ_HANDER[2] = _wcsdup(L"주소");
}

void OccurError(wchar_t* msg, char* file, int line) {
	fprintf(stderr, "%s:%d", file, line);
	fwprintf(stderr, L"%ls\n", msg);
	exit(1);
}

void _OccurError(errno_t n, char* file, int line) {
	wchar_t buf[BUFFER_SIZE + 1] = { 0 };
	strerror_s(buf, BUFFER_SIZE, n);
	OccurError(buf, file, line);
}

int binarySearch(void* arr, int start, int end, void* key, size_t elemSize, int (*func)(void*, void*)) {

	if (start > end)
		return -1;

	int mid = (end + start) / 2;
	void* elem = (char*)arr + (mid * elemSize);
	int funcRet = func(elem, key);
	if (funcRet == 0)
		return mid;
	else if (funcRet > 0)
		return binarySearch(arr, start, mid - 1, key, elemSize, func);
	else
		return binarySearch(arr, mid + 1, end, key, elemSize, func);
}
