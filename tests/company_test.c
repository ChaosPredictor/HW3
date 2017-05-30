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

	ASSERT_TEST( setGetSize(companies) == 0 );

	addCompany(companies, "sdfefdgdfh565@654fgjhfgsdf", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 1 );

	addCompany(companies, "sdfefdgdfh565@654fgjhfgsdf", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 1 );

	addCompany(companies, "sdfefdgdfh565@654fgjhfgsdg", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 2 );

	setClear(companies);

	ASSERT_TEST( setGetSize(companies) == 0 );

	setDestroy(companies);

	return true;
}


static bool testRemoveCompany() {

	Set companies = setCreate(copyCompany, freeCompany, compareCompanies);
	ASSERT_TEST( companies != NULL);

	ASSERT_TEST( setGetSize(companies) == 0 );

	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdf", CIVIL_ENGINEERING);

	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdg", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 2 );

	removeCompany( companies, "sdfefdgdfh565@654fgjhfgsdg" );

	ASSERT_TEST( setGetSize(companies) == 1 );

	setClear(companies);

	ASSERT_TEST( setGetSize(companies) == 0 );

	setDestroy(companies);

	return true;
}


static bool testEmailValidity() {
	ASSERT_TEST( emailValidity("45@$#") );
	ASSERT_TEST( !emailValidity("45^$#") );
	ASSERT_TEST( !emailValidity("45@@#") );
	return true;
}

static bool testOtherSetCompanyFunctions() {
	Set companies = setCreate(copyCompany, freeCompany, compareCompanies);
	ASSERT_TEST( companies != NULL );

	Company company1 = malloc(sizeof(struct company_t));
	char* email1 = "sdf@fdgdfh56";
	company1->email = malloc(sizeof(char) * (strlen(email1) + 1));
	strcpy(company1->email, email1);
	company1->faculty = CIVIL_ENGINEERING;

	Company company2 = malloc(sizeof(struct company_t));
	char* email2 = "sdf@fdgdfh57";
	company2->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(company2->email, email2);
	company2->faculty = CIVIL_ENGINEERING;

	Company company3 = malloc(sizeof(struct company_t));
	char* email3 = "sdf@fdgdfh58";
	company3->email = malloc(sizeof(char) * (strlen(email3) + 1));
	strcpy(company3->email, email1);
	company3->faculty = CIVIL_ENGINEERING;

	Company company4 = malloc(sizeof(struct company_t));
	char* email4 = "sdf@fdgdfh59";
	company4->email = malloc(sizeof(char) * (strlen(email4) + 1));
	strcpy(company4->email, email1);
	company4->faculty = CIVIL_ENGINEERING;

	addCompany(companies, "sdf@fdgdfh56", CIVIL_ENGINEERING);
	addCompany(companies, "sdf@fdgdfh57", CIVIL_ENGINEERING);
	addCompany(companies, "sdf@fdgdfh58", CIVIL_ENGINEERING);
	addCompany(companies, "sdf@fdgdfh59", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 4 );

	ASSERT_TEST( setIsIn(companies, company1) );
	ASSERT_TEST( setIsIn(companies, company2) );
	ASSERT_TEST( setIsIn(companies, company3) );
	ASSERT_TEST( setIsIn(companies, company4) );

	Set newCompanies = setCopy(companies);

	ASSERT_TEST( setIsIn(newCompanies, company1) );
	ASSERT_TEST( setIsIn(newCompanies, company2) );
	ASSERT_TEST( setIsIn(newCompanies, company3) );
	ASSERT_TEST( setIsIn(newCompanies, company4) );


	ASSERT_TEST( setGetSize(newCompanies) == 4 );

	freeCompany(company1);
	freeCompany(company2);
	freeCompany(company3);
	freeCompany(company4);
	setDestroy(companies);
	setDestroy(newCompanies);
	return true;
}

int main (int argv, char** arc){
	RUN_TEST(testCopyCompany);
	RUN_TEST(testFreeCompany);
	RUN_TEST(testCompareCompany);
	RUN_TEST(testAddCompany);
	RUN_TEST(testRemoveCompany);
	RUN_TEST(testEmailValidity);
	RUN_TEST(testOtherSetCompanyFunctions);


	return 0;
}
