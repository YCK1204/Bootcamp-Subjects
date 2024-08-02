#ifndef CONTACTDATA_H
#define CONTACTDATA_H

#include "Define.h"
#include <stdbool.h>
#include "MyLib.h"
#include "FileSystem.h"

#pragma region Free
void FreeContactData(ContactData* data, bool all);
void FreeContactTableData(TupleContactTable* tct);
#pragma endregion

#pragma region Generate
ContactData* GenerateContactDataByString(wchar_t** strs);
ContactData* GenerateContactDataByElems(wchar_t* name, wchar_t* number, wchar_t* addr);
#pragma endregion

#pragma region Compare
int ComparePhoneNumber(void* a, void* b);
int CompareAddress(void* a, void* b);
int CompareName(void* a, void* b);
int CompareContactData(const void* a, const void* b);
#pragma endregion

TupleContactTable* GetContactTableData();
wchar_t* ContactTableDataToString(TupleContactTable ctd);
void SetContactRange(ContactData* contacts, size_t size, size_t pos, int (*func)(void*, void*), int* start, int* end, ContactData* key);
void CopyContactData(ContactData* a, ContactData* b);
#endif