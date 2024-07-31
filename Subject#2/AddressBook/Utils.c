#include "Utils.h"
#include "FileSystem.h"
#include "Execute.h"
#include "MyLib.h"

void Init() {
	InitFiles();
	InitCmdHandler();
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

PhoneBookData* ConvertPhoneBookData(wchar_t** strs) {
	PhoneBookData* ret = (PhoneBookData*)malloc(sizeof(PhoneBookData));

	ret->number = strs[0];
	return ret;
}

ContactData* ConvertContactData(wchar_t** strs) {
	ContactData* ret = (ContactData*)malloc(sizeof(ContactData));

	ret->name = strs[0];
	ret->phoneNumber = strs[1];
	ret->address = strs[2];
	return ret;
}

TuplePhoneBookTable GetPhoneBookTableData() {
	TuplePhoneBookTable ret;

	wchar_t* str = FileToString(phoneBookFile);
	wchar_t** rows = Split(str, '\n', false);
	int size = Get2PCharSize(rows);

	ret.size = size;
	// 1을 추가하는 이유는  나중에 값을 삽입하고 정렬 하는 과정에서 realloc하는 과정을 줄이기 위함
	PhoneBookData* pb = (PhoneBookData*)calloc(sizeof(PhoneBookData), size + 1);
	ret.pb = pb;

	if (size == 0)
		return ret;
																				 
	for (size_t i = 0; i < size; i++) {
		pb[i].number = _wcsdup(rows[i]);
	}
	Free2P(rows, size);
	return ret;
}

TupleContactTable GetContactTableData() {
	TupleContactTable ret;

	wchar_t* str = FileToString(contactsFile);
	wchar_t** rows = Split(str, '\n', false);
	int size = Get2PCharSize(rows);

	ret.size = size;
	// 1을 추가하는 이유는  나중에 값을 삽입하고 정렬 하는 과정에서 realloc하는 과정을 줄이기 위함
	ContactData* contacts = (ContactData*)calloc(sizeof(ContactData), size + 1);
	ret.contacts = contacts;

	if (size == 0)
		return ret;
	for (size_t i = 0; i < size; i++) {
		wchar_t** strs = Split(rows[i], ',', false);

		ContactData* data = ConvertContactData(strs);
		contacts[i].name = _wcsdup(data->name);
		contacts[i].phoneNumber = _wcsdup(data->phoneNumber);
		contacts[i].address = _wcsdup(data->address);
		free(data);
		Free2P(strs, Get2PCharSize(strs));
	}
	Free2P(rows, size);
	return ret;
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

void FreePhoneBookData(PhoneBookData* data) {
	if (data == NULL)
		return;
	free(data->number);
	free(data);
}

void FreeContactData(ContactData* data) {
	if (data == NULL)
		return;
	free(data->address);
	free(data->name);
	free(data->phoneNumber);
	free(data);
}