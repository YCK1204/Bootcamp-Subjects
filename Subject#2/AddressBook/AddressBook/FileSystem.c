#include "FileSystem.h"
#include "Utils.h"
#include <locale.h>
#include "MyLib.h"

wchar_t* FileToString(FILE* fp) {
	if (fp == NULL)
		return NULL;

	wchar_t* ret = _wcsdup(L"");
	long initialPos = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	while (!feof(fp)) {
		wchar_t* line = Getline(fp);
		if (line == NULL)
			break;

		if (!feof(fp))
			ReplaceString(&line, StrJoin(line, L"\n"));
		ReplaceString(&ret, StrJoin(ret, line));
		free(line);
	}
	fseek(fp, initialPos, SEEK_SET);
	if (wcslen(ret) == 0) { // utf-8 without BOM
		free(ret);
		return NULL;
	}
	return ret;
}

void UpdateFile(FILE* fp, wchar_t* str, const char* path) {
	if (freopen_s(&fp, path, "w+, ccs=UNICODE", fp) != 0)
		_OccurError(errno, __FILE__, __LINE__);

	if (fputws(str, fp) == EOF)
		OccurError(L"Error : Failed to write to file", __FILE__, __LINE__);
}

void AppendDataToFile(FILE* fp, wchar_t* str)
{
	int pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	if (ftell(fp) > 0)
	{
		if (fputws(L"\n", fp) == EOF)
			OccurError(L"Error : Failed to write to file", __FILE__, __LINE__);
	}
	if (fputws(str, fp) == EOF)
		OccurError(L"Error : Failed to write to file", __FILE__, __LINE__);
	fseek(fp, pos, SEEK_SET);
}

bool IsEmptyFile(FILE* fp) {
	int pos = ftell(fp);
	fseek(fp, 0, SEEK_END);

	bool empty = (ftell(fp) == 0);
	fseek(fp, pos, SEEK_SET);
	return empty;
}