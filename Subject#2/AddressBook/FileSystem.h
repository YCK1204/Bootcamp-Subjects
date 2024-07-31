#ifndef FILESYSTEM_H
# define FILESYSTEM_H

# include <stdio.h>
#include "Define.h"

void InitFiles();
wchar_t* FileToString(FILE* f);
wchar_t* _FileToString(char* path);
void UpdateFile(FILE* fp, wchar_t* str);

#endif