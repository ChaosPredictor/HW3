#include "escaper_test.h"

static bool testCopyEscaper() {

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

	free(newEscaper->email);
	free(newEscaper);

	free(escaper->email);
	free(escaper);


	return true;
}

static bool testFreeEscaper() {

	freeEscaper(NULL);

	Escaper escaper = malloc(sizeof(struct escaper_t));
	char* email = "qazxsw@edcvfr";
	escaper->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(escaper->email, email);
	escaper->faculty = CIVIL_ENGINEERING;

	Escaper newEscaper = copyEscaper(escaper);

	freeEscaper(newEscaper);
	freeEscaper(escaper);


	return true;
}

static bool testCompareCompanies() {

	Escaper escaper = malloc(sizeof(struct escaper_t));
	char* email = "qazxsw@edcvfr";
	escaper->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(escaper->email, email);
	escaper->faculty = CIVIL_ENGINEERING;

	Escaper newEscaper = copyEscaper(escaper);

	ASSERT_TEST( newEscaper != NULL);
	ASSERT_TEST( strcmp(escaper->email,newEscaper->email) == 0);
	ASSERT_TEST( escaper->faculty == newEscaper->faculty );

	ASSERT_TEST( compareCompanies(escaper, newEscaper) == 0 );

	char* email2 = "qazxsw@edcvfp";
	free(escaper->email);
	escaper->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(escaper->email, email2);

	ASSERT_TEST( compareCompanies(escaper, newEscaper) != 0 );

	free(newEscaper->email);
	free(newEscaper);

	free(escaper->email);
	free(escaper);

	return true;
}

static bool testCreateEscaper() {

	EscapeSystem sys = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( sys != NULL);
	ASSERT_TEST( createSystem(sys) == MTM_SUCCESS );

	ASSERT_TEST( setGetSize(sys->escapers) == 0 );

	ASSERT_TEST( addEscaper(NULL, "escaper1@civil", CIVIL_ENGINEERING, 1 ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(sys, NULL, CIVIL_ENGINEERING , 1) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(sys, "escaper1#civil", CIVIL_ENGINEERING,1 ) == MTM_INVALID_PARAMETER);


	ASSERT_TEST( addEscaper(sys, "escaper1@civil", CIVIL_ENGINEERING,1 ) == MTM_SUCCESS );


	ASSERT_TEST( addEscaper(sys, "escaper1@civil", CIVIL_ENGINEERING, 1 ) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( addEscaper(sys, "escaper1@civil", MECHANICAL_ENGINEERING, 1 ) == MTM_EMAIL_ALREADY_EXISTS );

	ASSERT_TEST( addEscaper(sys, "escaperr2@civil", CIVIL_ENGINEERING ,1 ) == MTM_SUCCESS );

	ASSERT_TEST( addEscaper(sys, "escaper4@electrical", ELECTRICAL_ENGINEERING ,1 ) == MTM_SUCCESS );

	ASSERT_TEST( setGetSize(sys->escapers) == 3 );

	destroySystem(sys);

	return true;
}

static bool testReturnEscaperFaculty() {
	EscapeSystem sys = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( sys != NULL);
	ASSERT_TEST( createSystem(sys) == MTM_SUCCESS );

	ASSERT_TEST( addEscaper(sys, "escaper1@civil", CIVIL_ENGINEERING ,1 ) == MTM_SUCCESS );
	ASSERT_TEST( addEscaper(sys, "escaper2@computer", COMPUTER_SCIENCE ,1 ) == MTM_SUCCESS );
	ASSERT_TEST( addEscaper(sys, "escaper4@electrical", ELECTRICAL_ENGINEERING ,1 ) == MTM_SUCCESS );

	Escaper escaper = setGetFirst(sys->escapers);
	ASSERT_TEST( returnEscaperFaculty( escaper ) == CIVIL_ENGINEERING );
	escaper = setGetNext(sys->escapers);
	ASSERT_TEST( returnEscaperFaculty( escaper ) == COMPUTER_SCIENCE ) ;

	escaper = setGetNext(sys->escapers);
	ASSERT_TEST( returnEscaperFaculty( escaper ) == ELECTRICAL_ENGINEERING );

	destroySystem(sys);
	return true;
}


int escaperTests () {
	printf("\n\n ================ Escaper Tests ================ \n\n");
	RUN_TEST(testCopyEscaper);
	RUN_TEST(testFreeEscaper);
	RUN_TEST(testCompareCompanies);
	RUN_TEST(testCreateEscaper);
	RUN_TEST(testReturnEscaperFaculty);

	return 0;
}
