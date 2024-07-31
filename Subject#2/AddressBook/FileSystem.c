#include "FileSystem.h"
#include "Utils.h"
#include <locale.h>
#include <stdbool.h>
#include "MyLib.h"

void InitFiles() {
	if (contactsFile != NULL) {
		fclose(contactsFile);
		contactsFile = NULL;
	}
	if (phoneBookFile != NULL) {
		fclose(phoneBookFile);
		phoneBookFile = NULL;
	}
	setlocale(LC_ALL, ".UTF-8");

	if (fopen_s(&contactsFile, CONTACTS_PATH, "r+, ccs=UTF-8") != 0) {
		if (fopen_s(&contactsFile, CONTACTS_PATH, "w+, ccs=UTF-8") != 0)
			_OccurError(errno, __FILE__, __LINE__);
	}
	if (fopen_s(&phoneBookFile, PHONEBOOK_PATH, "r+, ccs=UTF-8") != 0) {
		if (fopen_s(&phoneBookFile, PHONEBOOK_PATH, "w+, ccs=UTF-8") != 0)
			_OccurError(errno, __FILE__, __LINE__);
	}
}

wchar_t* FileToString(FILE* fp) {
	if (fp == NULL)
		return NULL;

	wchar_t* ret = _wcsdup(L"");
	long initialPos = ftell(fp);
	while (!feof(fp)) {
		wchar_t* line = Getline(fp);
		if (line == NULL)
			break;

		if (!feof(fp))
			ReplaceString(&line, StrJoin(line, L"\n"));
		ReplaceString(&ret, StrJoin(ret, line));
	}
	fseek(fp, initialPos, SEEK_SET);
	return ret;
}

wchar_t* _FileToString(char* path) {
	FILE* fp = fopen(path, "r+, ccs=UTF-8");
	wchar_t* ret = FileToString(fp);
	fclose(fp);
	return ret;
}

void UpdateFile(FILE* fp, wchar_t* str) {
	if (fputws(str, fp) == EOF)
		OccurError(L"Error : Failed to write to file", __FILE__, __LINE__);
}
