#ifndef DEFINE_H
# define DEFINE_H

#include <stdio.h>

extern wchar_t** CMD_HANDLER;
extern void (*CMD[6])(void);
extern FILE* contactsFile;
extern FILE* phoneBookFile;
extern size_t MAX_ID;
# define CONTACTS_PATH "contacts.csv"
# define PHONEBOOK_PATH "phone_book.csv"

typedef enum {
	EXIT,
	CREATE,
	READ,
	UPDATE,
	DELETE,
	NONE,
} CmdType;

typedef struct {
	wchar_t* name;
	wchar_t* phoneNumber;
	wchar_t* address;
} ContactData;

typedef struct {
	wchar_t* number;
} PhoneBookData;

typedef struct {
	size_t size;
	PhoneBookData* pb;
} TuplePhoneBookTable;

typedef struct {
	size_t size;
	ContactData* contacts;
} TupleContactTable;

#endif