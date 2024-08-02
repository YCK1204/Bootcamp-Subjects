#include "Execute.h"
#include "FileSystem.h"
#include "MyLib.h"
#include "Define.h"
#include "Utils.h"
#include "ContactData.h"

void NavigateCommand(wchar_t* cmd) {
	size_t i = 0;
	CmdType type = NONE;

	for (; i < NONE; i++) {
		if (!MyStrcmp(CMD_HANDLER[i], cmd)) {
			type = (CmdType)i;
			break;
		}
	}

	CMD[type]();
}

#pragma region Create
void Create() {
	wprintf(L"이름 (2 ~ 12자), 휴대폰 번호 (010-0000-0000), 주소(~ 30자)\n");

	wchar_t* name = Readline(L"Create > 이름 : ");
	wchar_t* number = Readline(L"Create > 휴대폰 번호 : ");
	wchar_t* addr = Readline(L"Create > 주소 : ");

	ContactData* cd = GenerateContactDataByElems(name, number, addr);

	TupleContactTable* tct = GetContactTableData();

	int pos = -1;

	if (tct->size > 0)
	{
		qsort(tct->contacts, tct->size, sizeof(ContactData), ComparePhoneNumber);
		binarySearch(
			tct->contacts,
			0,
			tct->size - 1,
			cd,
			sizeof(ContactData),
			ComparePhoneNumber);
	}

	if (pos >= 0)
	{
		fwprintf(stderr, L"Error: phone number overlap\n");
	}
	else
	{
		tct->contacts[tct->size].address = _wcsdup(cd->address);
		tct->contacts[tct->size].name = _wcsdup(cd->name);
		tct->contacts[tct->size].phoneNumber = _wcsdup(cd->phoneNumber);

		tct->size++;
		wchar_t* textOfContactTabe = ContactTableDataToString(*tct);
		UpdateFile(contactsFile, textOfContactTabe, CONTACTS_PATH);
	}
	FreeContactData(cd, false);
	free(name);
	free(number);
	free(addr);
	FreeContactTableData(tct);
}
#pragma endregion

#pragma region Read
TupleContactTable* ReadHandler(wchar_t* key, ContactData* value, TupleContactTable fileData, int (*func)(void*, void*))
{
	TupleContactTable* ret = (TupleContactTable*)malloc(sizeof(TupleContactTable));
	ret->size = 0;
	ret->contacts = NULL;

	qsort(fileData.contacts, fileData.size, sizeof(ContactData), func);
	int pos = binarySearch(fileData.contacts, 0, fileData.size - 1, value, sizeof(ContactData), func);
	if (pos >= 0)
	{
		int start, end;
		SetContactRange(fileData.contacts, fileData.size, pos, func, &start, &end, value);
		ret->size = (end - start + 1);
		ret->contacts = (ContactData*)malloc(sizeof(ContactData) * ret->size);
		for (int i = start; i <= end; i++)
			CopyContactData(&ret->contacts[i - start], &fileData.contacts[i]);
	}
	return ret;
}

TupleContactTable* ExtractDataByAndConditionsHandler(wchar_t* key, wchar_t* value, TupleContactTable fileData)
{
	TupleContactTable* ret;
	ContactData tmpData;

	int i = 0;
	for (; i < 3; i++) {
		if (MyStrcmp(READ_HANDER[i], key) == 0)
			break;
	}
	switch (i)
	{
	case 0:
		tmpData.name = value;
		ret = ReadHandler(key, &tmpData, fileData, CompareName, CompareName);
		break;
	case 1:
		tmpData.phoneNumber = value;
		ret = ReadHandler(key, &tmpData, fileData, ComparePhoneNumber, ComparePhoneNumber);
		break;
	case 2:
		tmpData.address = value;
		ret = ReadHandler(key, &tmpData, fileData, CompareAddress, CompareAddress);
		break;
	default:
		ret = malloc(sizeof(TupleContactTable));
		ret->size = -1;
		ret->contacts = NULL;
		wprintf(L"%ls \'%ls\'를 가진 데이터가 없습니다.\n", key, value);
		break;
	}
	return ret;
}

TupleContactTable* FindCommonData(TupleContactTable* a, TupleContactTable* b)
{
	TupleContactTable* ret = (TupleContactTable*)malloc(sizeof(TupleContactTable));
	if (a->size == 0)
	{
		ret->contacts = (ContactData*)malloc(sizeof(ContactData) * b->size);
		ret->size = b->size;
		for (int i = 0; i < ret->size; i++)
			CopyContactData(&ret->contacts[i], &b->contacts[i]);
	}
	else
	{
		qsort(a->contacts, a->size, sizeof(ContactData), ComparePhoneNumber);
		qsort(b->contacts, b->size, sizeof(ContactData), ComparePhoneNumber);

		int maxSize = (a->size > b->size) ? a->size : b->size;
		ret->contacts = (ContactData*)malloc(sizeof(ContactData) * maxSize);
		ret->size = 0;

		for (int i = 0; i < a->size; i++)
		{
			// 중복 제거
			if (i > 0 && MyStrcmp(a->contacts[i - 1].phoneNumber, a->contacts[i].phoneNumber) == 0)
				continue;
			if (binarySearch(b->contacts, 0, b->size - 1, &a->contacts[i], sizeof(ContactData), ComparePhoneNumber) >= 0)
			{
				CopyContactData(&ret->contacts[ret->size], &a->contacts[i]);
				ret->size++;
			}
		}
	}
	FreeContactTableData(a);
	FreeContactTableData(b);
	return ret;
}

TupleContactTable* ExtractDataByAndConditions(wchar_t* condition, TupleContactTable fileData)
{
	TupleContactTable* ret = (TupleContactTable*)malloc(sizeof(TupleContactTable));
	ret->size = 0;
	ret->contacts = NULL;

	wchar_t** andConditions = Split(condition, '&', true);
	for (size_t i = 0; andConditions[i]; i++)
	{
		bool isValid = true;
		wchar_t** keyAndValue = Split(andConditions[i], '=', true);

		size_t size = Get2PCharSize(keyAndValue);
		isValid &= (size == 2);

		// 알맞게 파싱된 경우
		if (isValid == true)
		{
			wchar_t* key = keyAndValue[0];
			wchar_t* value = keyAndValue[1];
			TupleContactTable* data = ExtractDataByAndConditionsHandler(key, value, fileData);

			// key값이 이상한 경우
			if (data->size == -1)
			{
				FreeContactTableData(data);
				isValid = false;
			}
			// 원하는 key, value 값이 있는 경우
			else if (data->size > 0)
			{
				ret = FindCommonData(ret, data);
			}
		}
		Free2P(keyAndValue, size);
		if (isValid == false)
		{
			FreeContactTableData(ret);
			fprintf(stderr, "Error : Conditions are not valid");
			ret->size = -1;
			break;
		}
	}
	Free2P(andConditions, Get2PCharSize(andConditions));
	return ret;
}

TupleContactTable* MergeAndTruncate(TupleContactTable* a, TupleContactTable* b)
{
	TupleContactTable* ret = (TupleContactTable*)malloc(sizeof(TupleContactTable));
	ret->size = 0;

	if (a->size == 0)
	{
		ret->contacts = (ContactData*)malloc(sizeof(ContactData) * b->size);
		ret->size = b->size;
		for (int i = 0; i < ret->size; i++)
			CopyContactData(&ret->contacts[i], &b->contacts[i]);
	}
	else
	{
		qsort(a->contacts, a->size, sizeof(ContactData), ComparePhoneNumber);
		qsort(b->contacts, b->size, sizeof(ContactData), ComparePhoneNumber);

		int size = a->size + b->size;
		ret->contacts = (ContactData*)malloc(sizeof(ContactData) * (size));
		for (int i = 0; i < a->size; i++)
		{
			if (binarySearch(b->contacts, 0, b->size, &a->contacts[i], sizeof(ContactData), ComparePhoneNumber) >= 0)
				continue;
			CopyContactData(&ret->contacts[ret->size], &a->contacts[i]);
			ret->size++;
		}
		for (int i = 0; i < b->size; i++)
		{
			CopyContactData(&ret->contacts[ret->size], &b->contacts[i]);
			ret->size++;
		}
	}
	FreeContactTableData(a);
	FreeContactTableData(b);
	return ret;
}

void Read() {
	TupleContactTable* fileData = GetContactTableData();
	if (fileData->size == 0)
	{
		wprintf(L"현재 데이터베이스가 비어있습니다.\n");
		FreeContactTableData(fileData);
		return;
	}

	wprintf(
		L"&와 |를 사용해 원하는 데이터를 추출하세요! \n"
		L"키와 값은 \'=\' 으로 구분짓습니다\n"
		L"사용가능한 키들 : 이름, 전화번호, 주소\n"
		L"ex) 이름 = 8조 & 전화번호 = 010-1234-5678 | 주소 = 서울특별시\n");

	wchar_t* condition = Readline(L"Read > ");
	ReplaceString(&condition, Trim(condition));
	wchar_t** orConditions = Split(condition, '|', true);
	size_t size = Get2PCharSize(orConditions);

	TupleContactTable* extractedData = (TupleContactTable*)malloc(sizeof(TupleContactTable));
	extractedData->size = 0;
	extractedData->contacts = NULL;

	for (size_t i = 0; i < size; i++)
	{
		TupleContactTable* data = ExtractDataByAndConditions(orConditions[i], *fileData);

		if (data->size == -1)
		{
			FreeContactTableData(extractedData);
			extractedData = NULL;
			break;
		}
		extractedData = MergeAndTruncate(extractedData, data);
	}
	if (extractedData != NULL)
	{
		qsort(extractedData->contacts, extractedData->size, sizeof(ContactData), CompareContactData);
		for (int i = 0; i < extractedData->size; i++)
			wprintf(L"이름 : %ls, 전화번호 : %ls, 주소 : %ls\n",
				extractedData->contacts[i].name,
				extractedData->contacts[i].phoneNumber,
				extractedData->contacts[i].address);

		FreeContactTableData(extractedData);
	}
	free(condition);
	Free2P(orConditions, size);
	FreeContactTableData(fileData);
}
#pragma endregion

#pragma region Update
void Update() {
	TupleContactTable* fileData = GetContactTableData();

	if (fileData->size == 0)
	{
		wprintf(L"현재 데이터베이스가 비어있습니다.");
		FreeContactTableData(fileData);
		return;
	}

	wprintf(L"변경 하고싶은 데이터의 전화번호를 입력하세요!\n");
	wchar_t* nextNumber = Readline(L"Update > ");

	qsort(fileData->contacts, fileData->size, sizeof(ContactData), ComparePhoneNumber);
	ContactData tmp;
	tmp.phoneNumber = nextNumber;
	int pos = binarySearch(fileData->contacts, 0, fileData->size - 1, &tmp, sizeof(ContactData), ComparePhoneNumber);

	if (pos == -1)
	{
		wprintf(L"%ls 전화번호를 가진 연락처가 없습니다.\n", nextNumber);
	}
	else
	{
		ContactData* data = &fileData->contacts[pos];
		wprintf(L"[변경 전] 이름 : %ls, 전화번호 : %ls, 주소 : %ls\n", data->name, data->phoneNumber, data->address);
		wprintf(L"변경할 데이터를 입력해주세요!\n");

		wchar_t* name = Readline(L"Update > 이름 : ");
		wchar_t* number = Readline(L"Update > 전화번호 : ");
		wchar_t* address = Readline(L"Update > 주소 : ");

		tmp.phoneNumber = number;
		if (binarySearch(fileData->contacts, 0, fileData->size - 1, &tmp, sizeof(ContactData), ComparePhoneNumber) >= 0)
		{
			wprintf(L"%ls 전화번호가 이미 존재합니다.\n", number);
			free(name);
			free(number);
			free(address);
		}
		else
		{
			ReplaceString(&fileData->contacts[pos].name, name);
			ReplaceString(&fileData->contacts[pos].phoneNumber, number);
			ReplaceString(&fileData->contacts[pos].address, address);

			wchar_t* text = ContactTableDataToString(*fileData);
			UpdateFile(contactsFile, text, CONTACTS_PATH);
			free(text);
			wprintf(L"[변경 후] 이름 : %ls, 전화번호 : %ls, 주소 : %ls\n", data->name, data->phoneNumber, data->address);
		}
	}

	free(nextNumber);
	FreeContactTableData(fileData);
}
#pragma endregion

#pragma region Delete
void Delete() {
	TupleContactTable* fileData = GetContactTableData();

	if (fileData->size == 0)
	{
		wprintf(L"현재 데이터베이스가 비어있습니다.");
		FreeContactTableData(fileData);
		return;
	}

	wprintf(L"삭제 하고싶은 데이터의 전화번호를 입력하세요!\n");
	wchar_t* delNumber = Readline(L"Delete > ");

	qsort(fileData->contacts, fileData->size, sizeof(ContactData), ComparePhoneNumber);
	ContactData tmp;
	tmp.phoneNumber = delNumber;
	int pos = binarySearch(fileData->contacts, 0, fileData->size - 1, &tmp, sizeof(ContactData), ComparePhoneNumber);

	if (pos == -1)
	{
		wprintf(L"%ls 전화번호를 가진 연락처가 없습니다.\n", delNumber);
	}
	else
	{
		TupleContactTable* updatedData = (TupleContactTable*)malloc(sizeof(TupleContactTable));
		updatedData->size = fileData->size - 1;
		updatedData->contacts = (ContactData*)malloc(sizeof(ContactData) * updatedData->size);
		int f = 0;
		for (int i = 0; i < updatedData->size; i++)
		{
			if (i == pos)
			{
				f = 1;
				continue;
			}
			CopyContactData(&updatedData->contacts[i - f], &fileData->contacts[i]);
		}
		wchar_t* text = ContactTableDataToString(*updatedData);
		UpdateFile(contactsFile, text, CONTACTS_PATH);
	}

	free(delNumber);
	FreeContactTableData(fileData);

}
#pragma endregion

#pragma region Exit
void Exit() {
	fclose(contactsFile);
	exit(0);
}
#pragma endregion

#pragma region None
void None() {
	fprintf(stderr, "Error : Invalid Cmd\n");
}
#pragma endregion
