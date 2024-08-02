#ifndef DEFINE_H
# define DEFINE_H

#include <stdio.h>

extern wchar_t** CMD_HANDLER;
extern void (*CMD[6])(void);
extern wchar_t** READ_HANDER;
extern FILE* contactsFile;
# define CONTACTS_PATH "contacts.csv"

typedef enum {
	CREATE,
	READ,
	UPDATE,
	DELETE,
	EXIT,
	NONE,
} CmdType;

typedef struct {
	wchar_t* name;
	wchar_t* phoneNumber;
	wchar_t* address;
} ContactData;

typedef struct {
	long size;
	ContactData* contacts;
} TupleContactTable;

#endif