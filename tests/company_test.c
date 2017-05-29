#include "./test_utilities.h"
//#include "../set.h"
#include "./../company.c"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./../mtm_escape.h"
#include <string.h>
#include <ctype.h>
#include "./../company.h"

/*
static ListElement copyString(ListElement str){
	assert(str);
	char* copy = malloc(strlen(str)+1);
	return copy != NULL ? strcpy(copy, str) : NULL;
}

static void freeString(ListElement str){
	free(str);
}

static bool isLongerThan(ListElement element, ListFilterKey number) {
	char* string = element;
    return strlen(string) > *(int*)number;
}

static int compareLexiStringLexicographical(ListElement element1, ListElement element2) {
    return strcmp((char*)element1, (char*)element2);
}

static int compareStringLength(ListElement element1, ListElement element2) {
    return strlen((char*)element1) - strlen((char*)element2);
}*/


static bool testCopyCompany() {

	ASSERT_TEST( copyCompany(NULL) == NULL);

	Company company = malloc(sizeof(struct company_t));
	char* email = "qazxsw@edcvfr";
	company->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(company->email, email);
	company->faculty = CIVIL_ENGINEERING;

	Company newCompany = copyCompany(company);

	ASSERT_TEST( newCompany != NULL);
	ASSERT_TEST( strcmp(company->email,newCompany->email) == 0);
	ASSERT_TEST( company->faculty == newCompany->faculty );

	free(newCompany->email);
	free(newCompany);

	free(company->email);
	free(company);

	return true;
}

static bool testFreeCompany() {

	//ASSERT_TEST( freeCompany(NULL) == NULL);
	freeCompany(NULL);

	Company company = malloc(sizeof(struct company_t));
	char* email = "qazxsw@edcvfr";
	company->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(company->email, email);
	company->faculty = CIVIL_ENGINEERING;

	Company newCompany = copyCompany(company);

	freeCompany(newCompany);
	freeCompany(company);

	return true;
}

static bool testCompareCompany() {

	ASSERT_TEST( copyCompany(NULL) == NULL);

	Company company = malloc(sizeof(struct company_t));
	char* email = "qazxsw@edcvfr";
	company->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(company->email, email);
	company->faculty = CIVIL_ENGINEERING;

	Company newCompany = copyCompany(company);

	ASSERT_TEST( newCompany != NULL);
	ASSERT_TEST( strcmp(company->email,newCompany->email) == 0);
	ASSERT_TEST( company->faculty == newCompany->faculty );

	ASSERT_TEST( compareCompanies(company, newCompany) == 0 );

	char* email2 = "qazxsw@edcvfp";
	free(company->email);
	company->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(company->email, email2);

	ASSERT_TEST( compareCompanies(company, newCompany) != 0 );

	free(newCompany->email);
	free(newCompany);

	free(company->email);
	free(company);

	return true;
}

static bool testAddCompany() {

	Set companies = setCreate(copyCompany, freeCompany, compareCompanies);
	ASSERT_TEST( companies != NULL);
/*
	addCompany(Set setCompany, const char* newEmail, TechnionFaculty faculty);

	Company company = malloc(sizeof(struct company_t));
	char* email = "qazxsw@edcvfr";
	company->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(company->email, email);
	company->faculty = CIVIL_ENGINEERING;

	Company newCompany = copyCompany(company);

	ASSERT_TEST( newCompany != NULL);
	ASSERT_TEST( strcmp(company->email,newCompany->email) == 0);
	ASSERT_TEST( company->faculty == newCompany->faculty );

	ASSERT_TEST( compareCompanies(company, newCompany) == 0 );

	char* email2 = "qazxsw@edcvfp";
	free(company->email);
	company->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(company->email, email2);

	ASSERT_TEST( compareCompanies(company, newCompany) != 0 );

	free(newCompany->email);
	free(newCompany);

	free(company->email);
	free(company);
*/
	return true;
}


int main (int argv, char** arc){
	RUN_TEST(testCopyCompany);
	RUN_TEST(testFreeCompany);
	RUN_TEST(testCompareCompany);
	RUN_TEST(testAddCompany);


	return 0;
}
