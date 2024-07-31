#include "Execute.h"
#include "FileSystem.h"
#include "MyLib.h"
#include "Define.h"
#include "Utils.h"

void InitCmdHandler() {
	CMD_HANDLER = (wchar_t**)malloc(sizeof(wchar_t*) * 6);
	CMD_HANDLER[0] = _wcsdup(L"exit");
	CMD_HANDLER[1] = _wcsdup(L"create");
	CMD_HANDLER[2] = _wcsdup(L"read");
	CMD_HANDLER[3] = _wcsdup(L"update");
	CMD_HANDLER[4] = _wcsdup(L"delete");
	CMD_HANDLER[5] = NULL;

	CMD[0] = Exit;
	CMD[1] = Create;
	CMD[2] = Read;
	CMD[3] = Update;
	CMD[4] = Delete;
	CMD[5] = None;
}

void NavigateCommand(wchar_t* cmd) {
	size_t i = 0;
	CmdType type = NONE;

	for (; i < NONE; i++) {
		if (!MyStrcmp(CMD_HANDLER[i], cmd)) {
			type = (CmdType)i;
			break;
		}
	}

	if (type == EXIT) {
		fclose(contactsFile);
		fclose(phoneBookFile);
		Exit();
	}
	else
		CMD[type]();
}

void None() {
	fprintf(stderr, "Error : Invalid Cmd\n");
}
#include <Windows.h>
void Exit() {
	

	
	//Sleep(1000);
	exit(EXIT_SUCCESS);
}

ContactData* BuildContactData(wchar_t* name, wchar_t* number, wchar_t* addr)
{
	ContactData* ret = (ContactData*)malloc(sizeof(ContactData));
	ret->name = _wcsdup(name);
	ret->phoneNumber = _wcsdup(number);
	ret->address = _wcsdup(addr);
	ReplaceString(&ret->name, Trim(ret->name));
	ReplaceString(&ret->phoneNumber, Trim(ret->phoneNumber));
	ReplaceString(&ret->address, Trim(ret->address));
	return ret;
}

PhoneBookData* BuildPhoneBookData(wchar_t* number)
{
	PhoneBookData* ret = (PhoneBookData*)malloc(sizeof(PhoneBookData));
	ret->number = _wcsdup(number);
	ReplaceString(&ret->number, Trim(ret->number));
	return ret;
}

int ComparePhoneNumber(void* a, void* b) {
	PhoneBookData* data = (PhoneBookData*)a;
	PhoneBookData* key = (PhoneBookData*)b;

	return MyStrcmp(data->number, key->number);
}

int CompareName(void* a, void* b) {
	ContactData* data = (ContactData*)a;
	ContactData* key = (ContactData*)b;

	return MyStrcmp(data->name, key->name);
}

void SetContactRange(ContactData* contacts, size_t size, size_t pos, wchar_t* name, int* start, int* end) {
	int low = 0, high = pos;

	while (low < high)
	{
		int mid = (low + high) / 2;
		if (MyStrcmp(contacts[mid].name, name) == -1) low = mid + 1;
		else high = mid - 1;
	}
	*start = low;

	low = pos;
	high = size - 1;
	while (low < high)
	{
		int mid = (low + high) / 2;
		if (MyStrcmp(contacts[mid].name, name) == 1) high = mid - 1;
		else low = mid + 1;
	}
	*end = low;
}

int CompareContactData(const void* a, const void* b) {
	ContactData* A = (ContactData*)a;
	ContactData* B = (ContactData*)b;
	
	int diff = MyStrcmp(A->name, B->name);
	if (diff == 0)
		diff = MyStrcmp(A->phoneNumber, B->phoneNumber);
	return diff;
}

int ComparePhoneBookData(const void* a, const void* b)
{
	PhoneBookData* A = (PhoneBookData*)a;
	PhoneBookData* B = (PhoneBookData*)b;

	return MyStrcmp(A->number, B->number);
}

wchar_t* ContactTableDataToString(TupleContactTable ctd)
{
	wchar_t* ret = _wcsdup(L"");
	for (size_t i = 0; i < ctd.size; i++)
	{
		ReplaceString(&ret, StrJoin(ret, ctd.contacts[i].name));
		ReplaceString(&ret, StrJoin(ret, L","));
		ReplaceString(&ret, StrJoin(ret, ctd.contacts[i].phoneNumber));
		ReplaceString(&ret, StrJoin(ret, L","));
		ReplaceString(&ret, StrJoin(ret, ctd.contacts[i].address));
		if (i + 1 != ctd.size)
			ReplaceString(&ret, StrJoin(ret, L"\n"));
	}
	return ret;
}

wchar_t* PhoneBookTableDataToString(TuplePhoneBookTable pbtd)
{
	wchar_t* ret = _wcsdup(L"");
	for (size_t i = 0; i < pbtd.size; i++)
	{
		ReplaceString(&ret, StrJoin(ret, pbtd.pb[i].number));
		if (i + 1 != pbtd.size)
			ReplaceString(&ret, StrJoin(ret, L"\n"));
	}
	return ret;
}

void Create() {
	wprintf(L"이름 (2 ~ 12자), 휴대폰 번호 (010-0000-0000), 주소(~ 30자)\n");

	wchar_t* name = Readline(L"이름 > ");
	wchar_t* number = Readline(L"휴대폰 번호 > ");
	wchar_t* addr = Readline(L"주소 > ");

	ContactData* cd = BuildContactData(name, number, addr);
	PhoneBookData* pbd = BuildPhoneBookData(number);

	TupleContactTable ctd = GetContactTableData();
	TuplePhoneBookTable pbtd = GetPhoneBookTableData();

	int pos = binarySearch(
		pbtd.pb,
		0,
		pbtd.size - 1,
		pbd,
		sizeof(PhoneBookData),
		ComparePhoneNumber);

	if (pos >= 0)
	{
		fwprintf(stderr, L"Error: phone number overlap\n");
	}
	else
	{
		ctd.contacts[ctd.size].address = _wcsdup(cd->address);
		ctd.contacts[ctd.size].name = _wcsdup(cd->name);
		ctd.contacts[ctd.size].phoneNumber = _wcsdup(cd->phoneNumber);
		pbtd.pb[pbtd.size].number = _wcsdup(pbd->number);
		
		ctd.size++;
		pbtd.size++;
		qsort(ctd.contacts, ctd.size, sizeof(ContactData), CompareContactData);
		qsort(pbtd.pb, pbtd.size, sizeof(PhoneBookData), ComparePhoneBookData);
		wchar_t* textOfContactTabe = ContactTableDataToString(ctd);
		wchar_t* textOfPhoneBookTable = PhoneBookTableDataToString(pbtd);
		InitFiles();
		fputws(textOfContactTabe, contactsFile);
		fputws(textOfPhoneBookTable, phoneBookFile);
		/*UpdateFile(&contactsFile, textOfContactTabe);
		UpdateFile(&phoneBookFile, textOfPhoneBookTable);*/
	}
	free(name);
	free(number);
	free(addr);
	for (size_t i = 0; i < ctd.size; i++)
	{
		free(ctd.contacts[i].address);
		free(ctd.contacts[i].name);
		free(ctd.contacts[i].phoneNumber);
	}
	free(ctd.contacts);
	for (size_t i = 0; i < pbtd.size; i++)
	{
		free(pbtd.pb[i].number);
	}
	free(pbtd.pb);
}

void Read() {

}

void Update() {

}

void Delete() {

}
