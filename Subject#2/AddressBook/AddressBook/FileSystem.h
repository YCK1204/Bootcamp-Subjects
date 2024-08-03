#ifndef FILESYSTEM_H
# define FILESYSTEM_H

# include <stdio.h>
#include "Define.h"
#include <stdbool.h>

wchar_t* FileToString(FILE* f);
void UpdateFile(FILE* fp, wchar_t* str, const char* path);
void AppendDataToFile(FILE* fp, wchar_t* str);
bool IsEmptyFile(FILE* fp);
#endif