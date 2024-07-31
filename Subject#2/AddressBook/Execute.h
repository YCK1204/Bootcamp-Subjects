#ifndef EXECUTE_H
# define EXECUTE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void InitCmdHandler();
void Exit();
void Create();
void Read();
void Update();
void Delete();
void None();
void NavigateCommand(wchar_t* cmd);

#endif