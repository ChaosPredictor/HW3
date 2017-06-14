/*
 * system_test.c
 *
 *  Created on: Jun 6, 2017
 *      Author: master
 */


#include "./system_test.h"


static bool testHelperAddCompanies(EscapeSystem sys) {
	addCompany(sys, "company1@civil", 0 );
	addCompany(sys, "company2@civil", 0 );
	addCompany(sys, "company1@electrical", 2 );
	ASSERT_TEST( setGetSize(sys->companies) == 3 );
	return true;
}

static bool testHelperAddRooms(EscapeSystem sys) {
	addRoom(sys, "company1@civil", 1, 4, 3, "00-24", 2);
	addRoom(sys, "company1@civil", 2, 4, 3, "00-24", 2);
	addRoom(sys, "company1@civil", 3, 4, 3, "00-24", 2);
	addRoom(sys, "company2@civil", 4, 4, 3, "00-24", 2);
	addRoom(sys, "company1@electrical", 1, 16, 2, "05-20", 8);

	ASSERT_TEST( setGetSize(sys->rooms) == 5 );

	return true;
}

static bool testHelperAddEscapers(EscapeSystem sys) {
	ASSERT_TEST(addEscaper(sys, "escaper1@civil", 0, 2) == MTM_SUCCESS );
	ASSERT_TEST(addEscaper(sys, "escaper2@civil", 0, 2) == MTM_SUCCESS );
	ASSERT_TEST(addEscaper(sys, "escaper1@electrical", 2, 9) == MTM_SUCCESS );

	ASSERT_TEST( setGetSize(sys->escapers) == 3 );
	return true;
}

static bool testHelperAddOrders(EscapeSystem sys) {
	ASSERT_TEST( addOrder(sys, "escaper1@civil", 0, 2, "0-5", 3) == \
			MTM_SUCCESS );
	ASSERT_TEST( addOrder(sys, "escaper2@civil", 0, 2, "0-7", 3) == \
			MTM_SUCCESS );

	Day day = listGetFirst(sys->days);
	ASSERT_TEST( listGetSize( day->dayOrders ) == 2 );

	ASSERT_TEST( addOrder(sys, "escaper1@civil", 0, 3, "1-5", 3) == \
			MTM_SUCCESS );
	ASSERT_TEST( addOrder(sys, "escaper1@electrical", 2, 1, "1-14", 1) == \
			MTM_SUCCESS );

	day = listGetFirst(sys->days);
	day = listGetNext(sys->days);
	ASSERT_TEST( listGetSize( day->dayOrders ) == 2 );
	return true;
}



static bool testCreateSystem() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	EscapeSystem nullSystem = NULL;

	ASSERT_TEST( createSystem(nullSystem) == MTM_NULL_PARAMETER );

	ASSERT_TEST( createSystem(system) == MTM_SUCCESS );

	destroySystem(system);
	return true;
}


static bool testDestroySystemy() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	EscapeSystem nullSystem = NULL;

	ASSERT_TEST( createSystem(system) == MTM_SUCCESS );

	ASSERT_TEST( destroySystem(nullSystem) == MTM_NULL_PARAMETER );
	ASSERT_TEST( destroySystem(system) == MTM_SUCCESS );

	return true;
}







static bool testAddACompany() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddEscapers(system);

	EscapeSystem nullSystem = NULL;


	char* email = "company1@civil";
	char* nullEmail = NULL;
	char* invalidEmail = "company1#electrical";
	char* existEscaperEmail = "escaper1@civil";


	TechnionFaculty faculty = CIVIL_ENGINEERING;
	TechnionFaculty invalidFaculty = UNKNOWN;
	TechnionFaculty invalidFaculty2 = -1;
	TechnionFaculty invalidFaculty3 = 19;

	ASSERT_TEST( addCompany(nullSystem, email, faculty) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, nullEmail, faculty) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, invalidEmail, faculty) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, email, invalidFaculty) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, email, invalidFaculty2) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, email, invalidFaculty3) == \
			MTM_INVALID_PARAMETER );

	ASSERT_TEST( addCompany(system, email, faculty) == MTM_SUCCESS );

	ASSERT_TEST( addCompany(system, email, faculty) == \
			MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( addCompany(system, existEscaperEmail, faculty) == \
			MTM_EMAIL_ALREADY_EXISTS );


	destroySystem(system);
	return true;
}

static bool testRemoveACompany() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddEscapers(system);
	testHelperAddCompanies(system);
	testHelperAddRooms(system);
	testHelperAddOrders(system);

	int numberOfRooms = setGetSize(system->rooms);

	EscapeSystem nullSystem = NULL;


	char* email = "company2@civil";
	char* nullEmail = NULL;
	char* invalidEmail = "company1#civil";
	char* doesNotExistEmail = "company999@civil";
	char* existEscaperEmail = "escaper1@civil";
	char* orderedCompanyEmail = "company1@civil";
	char* orderedCompanyEmail2 = "company1@electrical";


	ASSERT_TEST( removeCompany(nullSystem, email) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeCompany(system, nullEmail) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeCompany(system, invalidEmail) == MTM_INVALID_PARAMETER );

	ASSERT_TEST( removeCompany(system, doesNotExistEmail) == \
			MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( removeCompany(system, existEscaperEmail) == \
			MTM_COMPANY_EMAIL_DOES_NOT_EXIST );

	ASSERT_TEST( removeCompany(system, orderedCompanyEmail) == \
			MTM_RESERVATION_EXISTS );
	ASSERT_TEST( removeCompany(system, orderedCompanyEmail2) == \
			MTM_RESERVATION_EXISTS );

	ASSERT_TEST( setGetSize(system->rooms) == numberOfRooms );
	ASSERT_TEST( removeCompany(system, email) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(system->rooms) < numberOfRooms );

	destroySystem(system);
	return true;
}

static bool testfindCompanyByEmail() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddEscapers(system);
	testHelperAddCompanies(system);

	Company company = malloc(sizeof(struct company_t));

	createCompany(company, "company1@civil", 0);

	char* email = "company1@civil";
	char* nullEmail = NULL;
	char* invalidEmail = "company1#electrical";
	char* existEscaperEmail = "escaper1@civil";

	ASSERT_TEST( findCompanyByEmail(system, nullEmail) == NULL );
	ASSERT_TEST( findCompanyByEmail(system, invalidEmail) == NULL );
	ASSERT_TEST( findCompanyByEmail(system, existEscaperEmail) == NULL );

	ASSERT_TEST( compareCompanies( findCompanyByEmail(system, email), \
			company) == 0 );

	freeCompany(company);
	destroySystem(system);
	return true;
}

static bool testisAnyRoomOfACompanyOrdered() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddCompanies( system );
	testHelperAddRooms( system );
	testHelperAddEscapers( system );
	testHelperAddOrders( system );


	char* orderedCompanyEmail = "company1@civil";
	char* doesNotOrderedCompanyEmail = "company2@civil";

	ASSERT_TEST(isAnyRoomOfACompanyOrdered(system,orderedCompanyEmail) == true);

	ASSERT_TEST( isAnyRoomOfACompanyOrdered(system, doesNotOrderedCompanyEmail)\
			== false );

	destroySystem(system);
	return true;
}




static bool testAddAnEscaper() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddCompanies(system);

	EscapeSystem nullSystem = NULL;


	char* email = "escaper1@civil";
	char* nullEmail = NULL;
	char* invalidEmail = "company1#electrical";
	char* existCompanyEmail = "company1@civil";


	TechnionFaculty faculty = CIVIL_ENGINEERING;
	TechnionFaculty invalidFaculty = UNKNOWN;
	TechnionFaculty invalidFaculty2 = -1;
	TechnionFaculty invalidFaculty3 = 19;
	SkillLevel skillLevel = 1;
	SkillLevel invalidSkillLevel = 0;
	SkillLevel invalidSkillLevel2 = 11;

	ASSERT_TEST( addEscaper(nullSystem, email, faculty, skillLevel) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(system, nullEmail, faculty, skillLevel) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(system, invalidEmail, faculty, skillLevel) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(system, email, invalidFaculty, skillLevel) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(system, email, invalidFaculty2, skillLevel) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(system, email, invalidFaculty3, skillLevel) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(system, email, faculty, invalidSkillLevel) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addEscaper(system, email, faculty, invalidSkillLevel2) == \
			MTM_INVALID_PARAMETER );

	ASSERT_TEST( addEscaper(system, existCompanyEmail, faculty, skillLevel) == \
			MTM_EMAIL_ALREADY_EXISTS );

	ASSERT_TEST( addEscaper(system, email, faculty, skillLevel) == MTM_SUCCESS);

	ASSERT_TEST( addEscaper(system, email, faculty, skillLevel) == \
			MTM_EMAIL_ALREADY_EXISTS );

	destroySystem(system);
	return true;
}

static bool testRemoveAnEscaper() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddEscapers(system);
	testHelperAddCompanies(system);
	testHelperAddRooms(system);
	testHelperAddOrders(system);



	EscapeSystem nullSystem = NULL;

	char* email = "escaper2@civil";
	char* nullEmail = NULL;
	char* invalidEmail = "escaper1#civil";
	char* doesNotExistEmail = "escaper999@civil";


	char* existCompanyEmail = "company1@civil";
	char* orderedEscaperEmail = "escaper1@civil";

	TechnionFaculty faculty = 0;
	int id = 3;

	ASSERT_TEST( removeEscaper(nullSystem, email) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeEscaper(system, nullEmail) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeEscaper(system, invalidEmail) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeEscaper(system, doesNotExistEmail) == \
			MTM_CLIENT_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( removeEscaper(system, existCompanyEmail) == \
			MTM_CLIENT_EMAIL_DOES_NOT_EXIST );


	ASSERT_TEST( removeEscaper(system, email) == MTM_SUCCESS );

	ASSERT_TEST( IsRoomOrdered(system, faculty, id) == true );

	ASSERT_TEST( removeEscaper(system, orderedEscaperEmail) == MTM_SUCCESS );

	ASSERT_TEST( IsRoomOrdered(system, faculty, id) == false );

	destroySystem(system);
	return true;
}

static bool testfindEscaperByEmail() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddEscapers(system);
	testHelperAddCompanies(system);

	Escaper escaper = malloc(sizeof(struct escaper_t));

	createEscaper(escaper, "escaper1@civil", 0, 5);

	char* email = "escaper1@civil";
	char* nullEmail = NULL;
	char* invalidEmail = "escaper1#electrical";
	char* existCompanyEmail = "company1@civil";

	ASSERT_TEST( findEscaperByEmail(system, nullEmail) == NULL );
	ASSERT_TEST( findEscaperByEmail(system, invalidEmail) == NULL );
	ASSERT_TEST( findEscaperByEmail(system, existCompanyEmail) == NULL );

	ASSERT_TEST( compareEscapers( findEscaperByEmail(system, email), \
			escaper) == 0 );

	freeEscaper(escaper);
	destroySystem(system);

	return true;
}




static bool testAddARoom() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddCompanies(system);

	EscapeSystem nullSystem = NULL;
	char* email = "company1@civil";
	char* nullEmail = NULL;
	char* invalidEmail = "company1#electrical";
	char* doesNotExistEmail = "company999@electrical";
	int id = 1;
	int invalidId = 0;
	int price = 4;
	int invalidPrice = 5;
	int invalidPrice2 = -4;
	int num_ppl = 3;
	int invalidNum_ppl = 0;
	char* working_hrs = "00-24";
	char* nullWorking_hrs = NULL;
	char* invalidWorking_hrs = "20-14";
	int difficulty = 2;
	int invalidDifficulty = 0;
	int invalidDifficulty2 = 11;

	ASSERT_TEST( addRoom(nullSystem, email, id, price, num_ppl, \
			working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, nullEmail, id, price, num_ppl, \
			working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, email, id, price, num_ppl, \
			nullWorking_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, invalidEmail, id, price, num_ppl, \
			working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, email, id, price, num_ppl, \
			invalidWorking_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, email, invalidId, price, num_ppl, \
			working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, email, id, invalidPrice, num_ppl, \
			working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, email, id, invalidPrice2, num_ppl, \
			working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, email, id, price, invalidNum_ppl, \
			working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, email, id, price, num_ppl, \
			working_hrs, invalidDifficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRoom(system, email, id, price, num_ppl, \
			working_hrs, invalidDifficulty2) == MTM_INVALID_PARAMETER );


	ASSERT_TEST( addRoom(system, doesNotExistEmail, id, price, num_ppl,\
			working_hrs, difficulty) == MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( addRoom(system, email, id, price, num_ppl, \
			working_hrs, difficulty) == MTM_SUCCESS );
	ASSERT_TEST( addRoom(system, email, id, price, num_ppl, \
			working_hrs, difficulty) == MTM_ID_ALREADY_EXIST );

	destroySystem(system);
	return true;
}

static bool testRemoveARoom() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem( system );
	testHelperAddCompanies( system );
	testHelperAddRooms( system );
	testHelperAddEscapers( system );
	testHelperAddOrders( system );

	EscapeSystem nullSystem = NULL;
	TechnionFaculty faculty = CIVIL_ENGINEERING;
	TechnionFaculty faculty2 = BIOMEDICAL_ENGINEERING;
	TechnionFaculty invalidFaculty = UNKNOWN;
	int id = 1;
	int orderedId = 2;
	int orderedId2 = 3;
	int invalidId = 0;
	int doesNotExistId = 999;

	ASSERT_TEST( removeRoom(nullSystem, faculty, id) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeRoom(system, invalidFaculty, id) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeRoom(system, faculty, invalidId) == \
			MTM_INVALID_PARAMETER );

	ASSERT_TEST( removeRoom(system, faculty, doesNotExistId) == \
			MTM_ID_DOES_NOT_EXIST );
	ASSERT_TEST( removeRoom(system, faculty2, id) == MTM_ID_DOES_NOT_EXIST );

	ASSERT_TEST( removeRoom(system, faculty, id) == MTM_SUCCESS );

	ASSERT_TEST( removeRoom(system, faculty, orderedId) == \
			MTM_RESERVATION_EXISTS );
	ASSERT_TEST( removeRoom(system, faculty, orderedId2) == \
			MTM_RESERVATION_EXISTS );

	destroySystem(system);
	return true;
}





static bool testAddAnOrder() {
	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddCompanies( system );
	testHelperAddRooms( system );
	testHelperAddEscapers( system );
	testHelperAddOrders( system );

	EscapeSystem invalidSystem = NULL;

	char* email = "escaper1@civil";
	char* invalidEmail = NULL;
	char* invalidEmail2 = "escaper1#civil";
	char* doesNotExistEmail = "escaper999@civil";
	char* existCompanyEmail = "company1@civil";
	TechnionFaculty faculty = CIVIL_ENGINEERING;

	TechnionFaculty invalidFaculty = UNKNOWN;
	TechnionFaculty doesNotExistFaculty = BIOMEDICAL_ENGINEERING;

	int id = 1;
	int roomOccupiedId = 2;
	int doesNotExistId = 999;

	char* time = "0-6";
	char* invalidTime = NULL;
	char* invalidTime2 = "0_6";
	char* escaperOccupiedTime = "0-5";
	char* roomOccupiedTime = "0-7";

	int num_ppl = 3;

	TechnionFaculty closeRoomFaculty = ELECTRICAL_ENGINEERING;
	char* loseRoomTime = "0-20";


	ASSERT_TEST( addOrder(invalidSystem, email, faculty, id, time, \
			num_ppl) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addOrder(system, invalidEmail, faculty, id, time, \
			num_ppl) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addOrder(system, invalidEmail2, faculty, id, time, \
			num_ppl) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addOrder(system, email, invalidFaculty, id, time, \
			num_ppl) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addOrder(system, email, faculty, id, invalidTime, \
			num_ppl) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addOrder(system, email, faculty, id, invalidTime2, \
			num_ppl) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addOrder(system, doesNotExistEmail, faculty, id, time, \
			num_ppl) == MTM_CLIENT_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( addOrder(system, existCompanyEmail, faculty, id, time, \
			num_ppl) == MTM_CLIENT_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( addOrder(system, email, faculty, doesNotExistId, time, \
			num_ppl) == MTM_ID_DOES_NOT_EXIST );
	ASSERT_TEST( addOrder(system, email, doesNotExistFaculty, id, time, \
			num_ppl) == MTM_ID_DOES_NOT_EXIST );
	ASSERT_TEST( addOrder(system, email, faculty, id, escaperOccupiedTime, \
			num_ppl) == MTM_CLIENT_IN_ROOM );
	ASSERT_TEST( addOrder(system, email, faculty, roomOccupiedId, \
			roomOccupiedTime, num_ppl) == MTM_ROOM_NOT_AVAILABLE );
	ASSERT_TEST( addOrder(system, email, closeRoomFaculty, id, loseRoomTime,\
			num_ppl) == MTM_ROOM_NOT_AVAILABLE );


	ASSERT_TEST( addOrder(system, email, faculty, id, time, num_ppl) == \
			MTM_SUCCESS );

	destroySystem(system);
	return true;
}

static bool testAddRecommendedOrder() {

	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	ASSERT_TEST( system != NULL );
	createSystem(system);
	testHelperAddEscapers( system );
	testHelperAddCompanies( system );


	EscapeSystem invalidSystem = NULL;

	char* email = "escaper1@civil";
	char* invalidEmail = NULL;
	char* invalidEmail2 = "escaper1#civil";
	char* doesNotExistEmail = "escaper999@civil";

	int num_ppl = 3;

	ASSERT_TEST( addRecommendedOrder(system, email, num_ppl) == \
			MTM_NO_ROOMS_AVAILABLE );

	testHelperAddRooms( system );
	testHelperAddOrders( system );

	ASSERT_TEST( addRecommendedOrder(invalidSystem, email, num_ppl) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRecommendedOrder(system, invalidEmail, num_ppl) == \
			MTM_INVALID_PARAMETER );
	ASSERT_TEST( addRecommendedOrder(system, invalidEmail2, num_ppl) == \
			MTM_INVALID_PARAMETER );

	ASSERT_TEST( addRecommendedOrder(system, doesNotExistEmail, num_ppl) == \
			MTM_CLIENT_EMAIL_DOES_NOT_EXIST );

	ASSERT_TEST( addRecommendedOrder(system, email, num_ppl) == MTM_SUCCESS );

	destroySystem(system);
	return true;
}




int systemTests () {
	printf("\n\n ================ System Tests ================ \n\n");

	RUN_TEST(testCreateSystem);
	RUN_TEST(testDestroySystemy);


	RUN_TEST(testAddACompany);
	RUN_TEST(testRemoveACompany);
	RUN_TEST(testfindCompanyByEmail);
	RUN_TEST(testisAnyRoomOfACompanyOrdered);

	RUN_TEST(testAddAnEscaper);
	RUN_TEST(testRemoveAnEscaper);
	RUN_TEST(testfindEscaperByEmail);


	RUN_TEST(testAddARoom);
	RUN_TEST(testRemoveARoom);



	RUN_TEST(testAddAnOrder);
	RUN_TEST(testAddRecommendedOrder);

	return 0;
}
