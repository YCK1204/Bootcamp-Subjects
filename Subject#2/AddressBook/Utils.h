#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "Define.h"
# define BUFFER_SIZE 1024 

void OccurError(wchar_t* msg, char* file, int line);
void Init();
void _OccurError(errno_t n, char* file, int line);
int binarySearch(void* arr, int start, int end, void* key, size_t elemSize, int (*func)(void*, void*));

#endif