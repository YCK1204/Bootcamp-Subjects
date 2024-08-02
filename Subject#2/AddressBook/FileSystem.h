#ifndef FILESYSTEM_H
# define FILESYSTEM_H

# include <stdio.h>
#include "Define.h"

wchar_t* FileToString(FILE* f);
void UpdateFile(FILE* fp, wchar_t* str, const char* path);

#endif