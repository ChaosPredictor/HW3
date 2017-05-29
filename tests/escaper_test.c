#include "./test_utilities.h"
#include "./../escaper.c"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./../mtm_escape.h"
#include <string.h>
#include <ctype.h>
#include "./../escaper.h"

static bool testCopyEscaper() {

/*	ASSERT_TEST( copyEscaper(NULL) == NULL);

	Escaper escaper = malloc(sizeof(struct escaper_t));
	char* email = "qazxsw@edcvfr";
	escaper->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(escaper->email, email);
	escaper->faculty = CIVIL_ENGINEERING;
	escaper->skill_level = 1;

	Escaper newEscaper = copyEscaper(escaper);

	ASSERT_TEST( newEscaper != NULL);
	ASSERT_TEST( strcmp(escaper->email,newEscaper->email) == 0);
	ASSERT_TEST( escaper->faculty == newEscaper->faculty );

	free(newEscaper->email);
	free(newEscaper);

	free(escaper->email);
	free(escaper);
*/
	return true;
}

static bool testFreeEscaper() {
/*
	//ASSERT_TEST( freeEscaper(NULL) == NULL);
	freeEscaper(NULL);

	Escaper escaper = malloc(sizeof(struct escaper_t));
	char* email = "qazxsw@edcvfr";
	escaper->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(escaper->email, email);
	escaper->faculty = CIVIL_ENGINEERING;

	Escaper newEscaper = copyEscaper(escaper);

	freeEscaper(newEscaper);
	freeEscaper(escaper);
*/
	return true;
}

static bool testCompareEscaper() {
/*
	ASSERT_TEST( copyEscaper(NULL) == NULL);

	Escaper escaper = malloc(sizeof(struct escaper_t));
	char* email = "qazxsw@edcvfr";
	escaper->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(escaper->email, email);
	escaper->faculty = CIVIL_ENGINEERING;

	Escaper newEscaper = copyEscaper(escaper);

	ASSERT_TEST( newEscaper != NULL);
	ASSERT_TEST( strcmp(escaper->email,newEscaper->email) == 0);
	ASSERT_TEST( escaper->faculty == newEscaper->faculty );

	ASSERT_TEST( compareEscaperes(escaper, newEscaper) == 0 );

	char* email2 = "qazxsw@edcvfp";
	free(escaper->email);
	escaper->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(escaper->email, email2);

	ASSERT_TEST( compareCompanies(escaper, newEscaper) != 0 );

	free(newEscaper->email);
	free(newEscaper);

	free(escaper->email);
	free(escaper);
*/
	return true;
}

static bool testAddEscaper() {
/*
	Set companies = setCreate(copyEscaper, freeEscaper, compareCompanies);
	ASSERT_TEST( companies != NULL);

	ASSERT_TEST( setGetSize(companies) == 0 );

	addEscaper(companies, "sdfefdgdfh5654654fgjhfgsdf", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 1 );

	addEscaper(companies, "sdfefdgdfh5654654fgjhfgsdf", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 1 );

	addEscaper(companies, "sdfefdgdfh5654654fgjhfgsdg", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 2 );

	setClear(companies);

	ASSERT_TEST( setGetSize(companies) == 0 );

	setDestroy(companies);
*/
	return true;
}

static bool testOtherSetEscaperFunctions() {
/*	Set companies = setCreate(copyEscaper, freeEscaper, compareCompanies);
	ASSERT_TEST( companies != NULL);

	Escaper escaper1 = malloc(sizeof(struct escaper_t));
	char* email1 = "sdfefdgdfh56";
	escaper1->email = malloc(sizeof(char) * (strlen(email1) + 1));
	strcpy(escaper1->email, email1);
	escaper1->faculty = CIVIL_ENGINEERING;

	Escaper escaper2 = malloc(sizeof(struct escaper_t));
	char* email2 = "sdfefdgdfh57";
	escaper2->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(escaper2->email, email2);
	escaper2->faculty = CIVIL_ENGINEERING;

	Escaper escaper3 = malloc(sizeof(struct escaper_t));
	char* email3 = "sdfefdgdfh58";
	escaper3->email = malloc(sizeof(char) * (strlen(email3) + 1));
	strcpy(escaper3->email, email1);
	escaper3->faculty = CIVIL_ENGINEERING;

	Escaper escaper4 = malloc(sizeof(struct escaper_t));
	char* email4 = "sdfefdgdfh59";
	escaper4->email = malloc(sizeof(char) * (strlen(email4) + 1));
	strcpy(escaper4->email, email1);
	escaper4->faculty = CIVIL_ENGINEERING;

	addEscaper(companies, "sdfefdgdfh56", CIVIL_ENGINEERING);
	addEscaper(companies, "sdfefdgdfh57", CIVIL_ENGINEERING);
	addEscaper(companies, "sdfefdgdfh58", CIVIL_ENGINEERING);
	addEscaper(companies, "sdfefdgdfh59", CIVIL_ENGINEERING);

	ASSERT_TEST( setGetSize(companies) == 4 );

	ASSERT_TEST( setIsIn(companies, escaper1) );
	ASSERT_TEST( setIsIn(companies, escaper2) );
	ASSERT_TEST( setIsIn(companies, escaper3) );
	ASSERT_TEST( setIsIn(companies, escaper4) );

	Set newCompanies = setCopy(companies);

	ASSERT_TEST( setIsIn(newCompanies, escaper1) );
	ASSERT_TEST( setIsIn(newCompanies, escaper2) );
	ASSERT_TEST( setIsIn(newCompanies, escaper3) );
	ASSERT_TEST( setIsIn(newCompanies, escaper4) );

	ASSERT_TEST( setGetSize(newCompanies) == 4 );

	freeEscaper(escaper1);
	freeEscaper(escaper2);
	freeEscaper(escaper3);
	freeEscaper(escaper4);
	setDestroy(companies);
	setDestroy(newCompanies);*/
	return true;
}

int main (int argv, char** arc) {
	RUN_TEST(testCopyEscaper);
	RUN_TEST(testFreeEscaper);
	RUN_TEST(testCompareEscaper);
	RUN_TEST(testAddEscaper);
	RUN_TEST(testOtherSetEscaperFunctions);


	return 0;
}
