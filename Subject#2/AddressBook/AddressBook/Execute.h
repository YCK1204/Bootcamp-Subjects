#ifndef EXECUTE_H
# define EXECUTE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Create();
void Read();
void Update();
void Delete();
void None();
void Exit();
void NavigateCommand(wchar_t* cmd);
int ComparePhoneNumber(void* a, void* b);

#endif