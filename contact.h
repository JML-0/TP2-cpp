#pragma once
#ifndef _CONTACT_H
#define _CONTACT_H

#include <string>
#include <vector>
#include <list>
#include <time.h>
using namespace std;

typedef struct AppelAbs
{
	string num;
	time_t date;
} AppelAbs;

typedef struct AppelES
{
	bool AppelEntrant;
	string num;
	time_t date;
} AppelES;

typedef struct Contact_
{
	string name, firstName;
	vector<string> Nums;
} *Contact;

list<Contact> Contacts;
list<AppelAbs> AppAbs;
list<AppelES> AppES;
string nameContact;
string firstNameContact;

extern void addContact(Contact);
extern void displayContacts();
extern void displayContacts1By1();
extern void displayContact(Contact);
extern Contact createContact(string, string, vector<string>);
extern bool contactExist(string, string);
extern bool compByName(Contact&, Contact&);
extern bool compByFirstName(Contact&, Contact&);
extern void findContact();
extern void deleteContact(Contact);
extern Contact getName(string);
extern void addAppelAbs(string);
extern void addAppelES(string, bool);
#endif