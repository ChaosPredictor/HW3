/*
 * company_test.c
 *
 *  Created on: Jun 12, 2017
 *      Author: master
 */

#include "company_test.h"

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

static bool testCompareCompanies() {

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

static bool testCreateCompany() {

	EscapeSystem sys = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( sys != NULL);
	ASSERT_TEST( createSystem(sys) == MTM_SUCCESS );

	ASSERT_TEST( setGetSize(sys->companies) == 0 );

	ASSERT_TEST( addCompany(NULL, "company1@civil", CIVIL_ENGINEERING ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(sys, NULL, CIVIL_ENGINEERING) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(sys, "company1#civil", CIVIL_ENGINEERING) == MTM_INVALID_PARAMETER);


	ASSERT_TEST( addCompany(sys, "company1@civil", CIVIL_ENGINEERING) == MTM_SUCCESS );


	ASSERT_TEST( addCompany(sys, "company1@civil", CIVIL_ENGINEERING ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( addCompany(sys, "company1@civil", MECHANICAL_ENGINEERING ) == MTM_EMAIL_ALREADY_EXISTS );

	ASSERT_TEST( addCompany(sys, "companyr2@civil", CIVIL_ENGINEERING ) == MTM_SUCCESS );

	ASSERT_TEST( addCompany(sys, "company4@electrical", ELECTRICAL_ENGINEERING ) == MTM_SUCCESS );

	ASSERT_TEST( setGetSize(sys->companies) == 3 );

	destroySystem(sys);

	return true;
}

static bool testReturnCompanyFaculty() {
	EscapeSystem sys = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( sys != NULL);
	ASSERT_TEST( createSystem(sys) == MTM_SUCCESS );

	ASSERT_TEST( addCompany(sys, "company1@civil", CIVIL_ENGINEERING) == MTM_SUCCESS );
	ASSERT_TEST( addCompany(sys, "company2@computer", COMPUTER_SCIENCE ) == MTM_SUCCESS );
	ASSERT_TEST( addCompany(sys, "company4@electrical", ELECTRICAL_ENGINEERING ) == MTM_SUCCESS );

	Company company = setGetFirst(sys->companies);
	ASSERT_TEST( returnCompanyFaculty( company ) == CIVIL_ENGINEERING );
	company = setGetNext(sys->companies);
	ASSERT_TEST( returnCompanyFaculty( company ) == COMPUTER_SCIENCE ) ;

	company = setGetNext(sys->companies);
	ASSERT_TEST( returnCompanyFaculty( company ) == ELECTRICAL_ENGINEERING );

	destroySystem(sys);
	return true;
}


int companyTests () {
	printf("\n\n ================ Company Tests ================ \n\n");
	RUN_TEST(testCopyCompany);
	RUN_TEST(testFreeCompany);
	RUN_TEST(testCompareCompanies);
	RUN_TEST(testCreateCompany);
	RUN_TEST(testReturnCompanyFaculty);

	return 0;
}
