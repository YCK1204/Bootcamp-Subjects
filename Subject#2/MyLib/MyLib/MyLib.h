#ifndef MYLIB_H
# define MYLIB_H

#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>

#define BUFFER_SIZE 1024
#define DLLEXPORT __declspec(dllexport)

DLLEXPORT wchar_t* Trim(wchar_t* str);
DLLEXPORT wchar_t* _Substr(wchar_t* str, size_t start);
DLLEXPORT wchar_t* Substr(wchar_t* str, size_t start, size_t count);
DLLEXPORT wchar_t* Getline(FILE* fp);
DLLEXPORT wchar_t* _Getline(int fd);
DLLEXPORT wchar_t** Split(wchar_t* str, int delim, bool trim);
DLLEXPORT wchar_t* StrJoin(wchar_t* s1, wchar_t* s2);
DLLEXPORT int StrFindByChar(wchar_t* str, wchar_t target, size_t pos);
DLLEXPORT int StrFindByString(wchar_t* str, wchar_t* target, size_t pos);
DLLEXPORT int StrRFindByChar(wchar_t* str, wchar_t target, size_t pos);
DLLEXPORT int StrRFindByString(wchar_t* str, wchar_t* target, size_t pos);
DLLEXPORT void ReplaceString(wchar_t** oldString, wchar_t* newString);
DLLEXPORT wchar_t* IntToAscii(int n);
DLLEXPORT wchar_t* CharToString(wchar_t c);
DLLEXPORT void _InsertString(wchar_t** original, size_t pos, wchar_t c);
DLLEXPORT void InsertString(wchar_t** original, size_t pos, wchar_t* str);
DLLEXPORT wchar_t* MyStrcpy(wchar_t* dest, wchar_t* src, size_t pos);
DLLEXPORT wchar_t* MyStrncpy(wchar_t* dest, wchar_t* src, size_t pos, size_t n);
DLLEXPORT void String_ToUpper(wchar_t* str);
DLLEXPORT void String_ToLower(wchar_t* str);
DLLEXPORT wchar_t* Readline(wchar_t* msg);
DLLEXPORT int MyStrcmp(wchar_t* s1, wchar_t* s2);
DLLEXPORT int Get2PCharSize(wchar_t** strs);
DLLEXPORT int StringToInt(wchar_t* str);
DLLEXPORT void Free2P(void** v, int size);

#endif