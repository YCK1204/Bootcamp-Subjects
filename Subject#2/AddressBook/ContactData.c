#include "ContactData.h"

#pragma region Free
void FreeContactData(ContactData* data, bool all) {
	if (data == NULL)
		return;
	free(data->address);
	free(data->name);
	free(data->phoneNumber);
	if (all == true)
		free(data);
}

void FreeContactTableData(TupleContactTable* tct)
{
	for (int i = 0; i < tct->size; i++)
		FreeContactData(&tct->contacts[i], false);
	free(tct->contacts);
	free(tct);
}
#pragma endregion

TupleContactTable* GetContactTableData() {
	TupleContactTable* ret = (TupleContactTable *)malloc(sizeof(TupleContactTable));

	wchar_t* str = FileToString(contactsFile);
	wchar_t** rows = Split(str, '\n', false);
	int size = Get2PCharSize(rows);

	ret->size = size;
	// 1을 추가하는 이유는  나중에 값을 삽입하고 정렬 하는 과정에서 realloc하는 과정을 줄이기 위함
	ContactData* contacts = (ContactData*)calloc(sizeof(ContactData), size + 1);
	ret->contacts = contacts;

	if (size == 0)
		return ret;
	for (size_t i = 0; i < size; i++) {
		wchar_t** strs = Split(rows[i], ',', false);

		ContactData* data = GenerateContactDataByString(strs);
		contacts[i].name = _wcsdup(data->name);
		contacts[i].phoneNumber = _wcsdup(data->phoneNumber);
		contacts[i].address = _wcsdup(data->address);
		free(data);
		Free2P(strs, Get2PCharSize(strs));
	}
	Free2P(rows, size);
	return ret;
}

#pragma region Generate
ContactData* GenerateContactDataByString(wchar_t** strs) {
	ContactData* ret = (ContactData*)malloc(sizeof(ContactData));

	ret->name = _wcsdup(strs[0]);
	ret->phoneNumber = _wcsdup(strs[1]);
	ret->address = _wcsdup(strs[2]);
	return ret;
}

ContactData* GenerateContactDataByElems(wchar_t* name, wchar_t* number, wchar_t* addr)
{
	ContactData* ret = (ContactData*)malloc(sizeof(ContactData));
	ret->name = _wcsdup(name);
	ret->phoneNumber = _wcsdup(number);
	ret->address = _wcsdup(addr);
	return ret;
}
#pragma endregion

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

void SetContactRange(ContactData* contacts, size_t size, size_t pos, int (*func)(void*, void*), int* start, int* end, ContactData* key) {
	int low = 0, high = pos;

	while (low <= high) {
		int mid = (low + high) / 2;
		if (func(&contacts[mid], key) < 0) low = mid + 1;
		else high = mid - 1;
	}
	*start = low;

	low = pos;
	high = size - 1;

	while (low <= high) {
		int mid = (low + high) / 2;
		if (func(&contacts[mid], key) > 0) high = mid - 1;
		else low = mid + 1;
	}
	*end = high;
}

#pragma region Compare
int CompareContactData(const void* a, const void* b) {
	ContactData* A = (ContactData*)a;
	ContactData* B = (ContactData*)b;

	int diff = MyStrcmp(A->name, B->name);
	if (diff == 0)
		diff = MyStrcmp(A->phoneNumber, B->phoneNumber);
	return diff;
}

int ComparePhoneNumber(void* a, void* b) {
	ContactData* data = (ContactData*)a;
	ContactData* key = (ContactData*)b;

	return MyStrcmp(data->phoneNumber, key->phoneNumber);
}

int CompareAddress(void* a, void* b)
{
	ContactData* data = (ContactData*)a;
	ContactData* key = (ContactData*)b;

	return MyStrcmp(data->address, key->address);
}

int CompareName(void* a, void* b) {
	ContactData* data = (ContactData*)a;
	ContactData* key = (ContactData*)b;

	return MyStrcmp(data->name, key->name);
}
#pragma endregion

void CopyContactData(ContactData* a, ContactData* b)
{
	a->name = _wcsdup(b->name);
	a->phoneNumber = _wcsdup(b->phoneNumber);
	a->address = _wcsdup(b->address);
}
