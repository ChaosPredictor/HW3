/*
 * system_test.c
 *
 *  Created on: Jun 6, 2017
 *      Author: master
 */


#include "./system_test.h"


/*
EscapeSystem testHelperUsers() {

	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	system->escapers = setCreate(copyEscaper, freeEscaper, compareEscapers);
	system->companies = setCreate(copyCompany, freeCompany, compareCompanies);


	//Set users = setCreate(copyUser, freeUser, compareUsers);
	ASSERT_TEST( system != NULL);

	addCompany( system, "company1@civil", CIVIL_ENGINEERING );
	addCompany( system, "company2@civil", CIVIL_ENGINEERING );
	addCompany( system, "company3@civil", CIVIL_ENGINEERING );
	addCompany( system, "company5@civil", CIVIL_ENGINEERING );
	addCompany( system, "company1@mechanical", MECHANICAL_ENGINEERING );
	addCompany( system, "company2@mechanical", MECHANICAL_ENGINEERING );
	addCompany( system, "company3@mechanical", MECHANICAL_ENGINEERING );
	addCompany( system, "company4@mechanical", MECHANICAL_ENGINEERING );
	addCompany( system, "company6@mechanical", MECHANICAL_ENGINEERING );
	addCompany( system, "company1@electrical", ELECTRICAL_ENGINEERING );
	addCompany( system, "company2@electrical", ELECTRICAL_ENGINEERING );
	addCompany( system, "company3@electrical", ELECTRICAL_ENGINEERING );
	addCompany( system, "company5@electrical", ELECTRICAL_ENGINEERING );
	addCompany( system, "company6@electrical", ELECTRICAL_ENGINEERING );
	addCompany( system, "company7@electrical", ELECTRICAL_ENGINEERING );
	addCompany( system, "company1@chemical", CHEMICAL_ENGINEERING );
	addCompany( system, "company1@biotechnology", BIOTECHNOLOGY_AND_FOOD_ENGINEERING );
	addCompany( system, "company1@aerospace", AEROSPACE_ENGINEERING );
	addCompany( system, "company1@industrial", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT );
	addCompany( system, "company1@mathematics", MATHEMATICS );
	addCompany( system, "company1@physics", PHYSICS );
	addCompany( system, "company1@chemistry", CHEMISTRY );
	addCompany( system, "company1@biology", BIOLOGY );
	addCompany( system, "company1@architecture", ARCHITECTURE );
	addCompany( system, "company1@education", EDUCATION_IN_TECH_AND_SCIENCE );
	addCompany( system, "company1@computer", COMPUTER_SCIENCE );
	addCompany( system, "company1@medicine", MEDICINE );
	addCompany( system, "company1@materials", MATERIALS_ENGINEERING );
	addCompany( system, "company1@humanites", HUMANITIES_AND_ARTS );
	addCompany( system, "company1@biomedical", BIOMEDICAL_ENGINEERING );

	addEscaper( system, "escaper1@civil", CIVIL_ENGINEERING, ESCAPER_1 );
	addEscaper( system, "escaper2@civil", CIVIL_ENGINEERING, ESCAPER_5 );
	addEscaper( system, "escaper3@mechanical", MECHANICAL_ENGINEERING, ESCAPER_2 );
	addEscaper( system, "escaper1@mechanical", MECHANICAL_ENGINEERING, ESCAPER_8 );
	addEscaper( system, "escaper1@electrical", ELECTRICAL_ENGINEERING, ESCAPER_10 );
	addEscaper( system, "escaper2@electrical", ELECTRICAL_ENGINEERING, ESCAPER_6 );
	addEscaper( system, "escaper1@physics", PHYSICS, ESCAPER_6 );
	addEscaper( system, "escaper1@biotechnology", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, ESCAPER_1 );
	addEscaper( system, "escaper1@aerospace", AEROSPACE_ENGINEERING, ESCAPER_7 );
	addEscaper( system, "escaper1@education", EDUCATION_IN_TECH_AND_SCIENCE, ESCAPER_9 );
	addEscaper( system, "escaper1@mathematics", MATHEMATICS, ESCAPER_7 );


	ASSERT_TEST( setGetSize(system->escapers) == 11 );
	ASSERT_TEST( setGetSize(system->companies) == 30 );

	return system;
}
*/
/*

static List testHelperAddOrderToADay(EscapeSystem *sys) {
	List days = (*sys)->days;
	Day day = listGetFirst(days);
	List orders = day->dayOrders;

	Set users = testHelperAddUsers();
	Set rooms = testHelperAddRooms(users);

	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@electrical", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, 2, "0-4", 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@electrical", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, 2, "0-5", 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@electrical", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, 2, "0-6", 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@education", CIVIL_ENGINEERING, 1, "0-12", 2) == MTM_SUCCESS );

	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@education", CIVIL_ENGINEERING, 1, "1-12", 2) == MTM_SUCCESS );

	//ASSERT_TEST( addOrder(days, users, rooms, "escaper1@electrical", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, 2, "0-4", 3) == MTM_ROOM_NOT_AVAILABLE );

	//printf("\nwhy? %d\n", addOrderToADay( orders, users, rooms, "escaper1@electrical", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, 2, 4, 3));




	//printAllDays(days);

	ASSERT_TEST( listGetSize(orders) == 4 );


	setDestroy(rooms);
	setDestroy(users);

	return days;

}


static EscapeSystem testHelperCreateSystem() {
	EscapeSystem *sys = NULL;
	createSystem(&sys);
	testHelperUsers(sys);

	//sys->users = testHelperAddUsers();
	//sys->rooms = testHelperAddRooms(*sys->users);
	//sys->days = testHelperAddOrderToADay();

	return *sys;
}



static bool testReportDay() {
	EscapeSystem *sys=NULL;

	testHelperCreateSystem(&sys);
	//printAllDays(days);
	reportDay(stdout, sys);

	listDestroy(sys);
	return true;
}*/



static bool testHelperAddCompanies(EscapeSystem sys) {
	addCompany(sys, "company1@civil", 0 );
	addCompany(sys, "company2@civil", 0 );
	addCompany(sys, "company1@electrical", 2 );
	ASSERT_TEST( setGetSize(sys->companies) == 3 );
	return true;
}

static bool testHelperAddRooms(EscapeSystem sys) {
	addARoom(sys, "company1@civil", 1, 4, 3, "00-24", 2);
	addARoom(sys, "company1@civil", 2, 4, 3, "00-24", 2);
	addARoom(sys, "company1@civil", 3, 4, 3, "00-24", 2);
	addARoom(sys, "company1@electrical", 1, 16, 2, "05-20", 8);

	ASSERT_TEST( setGetSize(sys->rooms) == 4 );

	return true;
}

static bool testHelperAddEscapers(EscapeSystem sys) {
	addAEscaper(sys, "escaper1@civil", 0, 2);
	addAEscaper(sys, "escaper1@electrical", 2, 9);

	ASSERT_TEST( setGetSize(sys->escapers) == 2 );
	return true;
}

static bool testHelperAddOrders(EscapeSystem sys) {
	addOrder(sys, "escaper1@civil", 0, 2, "0-5", 3);

	Day day = listGetFirst(sys->days);
	ASSERT_TEST( listGetSize( day->dayOrders ) == 1 );
	addOrder(sys, "escaper1@civil", 0, 3, "1-5", 3);

	addOrder(sys, "escaper1@electrical", 2, 1, "1-14", 1);

	day = listGetFirst(sys->days);
	day = listGetNext(sys->days);
	ASSERT_TEST( listGetSize( day->dayOrders ) == 2 );
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
	//TechnionFaculty faculty2 = BIOMEDICAL_ENGINEERING;
	TechnionFaculty invalidFaculty = UNKNOWN;
	TechnionFaculty invalidFaculty2 = -1;
	TechnionFaculty invalidFaculty3 = 19;

	ASSERT_TEST( addCompany(nullSystem, email, faculty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, nullEmail, faculty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, invalidEmail, faculty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, invalidEmail, faculty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, email, invalidFaculty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, email, invalidFaculty2) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addCompany(system, email, invalidFaculty3) == MTM_INVALID_PARAMETER );

	ASSERT_TEST( addCompany(system, email, faculty) == MTM_SUCCESS );

	ASSERT_TEST( addCompany(system, email, faculty) == MTM_EMAIL_ALREADY_EXISTS );
	ASSERT_TEST( addCompany(system, existEscaperEmail, faculty) == MTM_EMAIL_ALREADY_EXISTS );


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


	EscapeSystem nullSystem = NULL;


	char* email = "company2@civil";
	char* nullEmail = NULL;
	char* invalidEmail = "company1#civil";
	char* doesNotexistEmail = "company999@civil";
	char* existEscaperEmail = "escaper1@civil";
	char* orderedcompanyEmail = "company1@civil";
	char* orderedcompanyEmail2 = "company1@electrical";


	ASSERT_TEST( removeCompany(nullSystem, email) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeCompany(system, nullEmail) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeCompany(system, invalidEmail) == MTM_INVALID_PARAMETER );

	ASSERT_TEST( removeCompany(system, doesNotexistEmail) == MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( removeCompany(system, existEscaperEmail) == MTM_COMPANY_EMAIL_DOES_NOT_EXIST );

	ASSERT_TEST( removeCompany(system, orderedcompanyEmail) == MTM_RESERVATION_EXISTS );
	ASSERT_TEST( removeCompany(system, orderedcompanyEmail2) == MTM_RESERVATION_EXISTS );


	ASSERT_TEST( removeCompany(system, email) == MTM_SUCCESS );



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

	ASSERT_TEST( addARoom(nullSystem, email, id, price, num_ppl, working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, nullEmail, id, price, num_ppl, working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, email, id, price, num_ppl, nullWorking_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, invalidEmail, id, price, num_ppl, working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, email, id, price, num_ppl, invalidWorking_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, email, invalidId, price, num_ppl, working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, email, id, invalidPrice, num_ppl, working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, email, id, invalidPrice2, num_ppl, working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, email, id, price, invalidNum_ppl, working_hrs, difficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, email, id, price, num_ppl, working_hrs, invalidDifficulty) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( addARoom(system, email, id, price, num_ppl, working_hrs, invalidDifficulty2) == MTM_INVALID_PARAMETER );


	ASSERT_TEST( addARoom(system, doesNotExistEmail, id, price, num_ppl, working_hrs, difficulty) == MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( addARoom(system, email, id, price, num_ppl, working_hrs, difficulty) == MTM_SUCCESS );
	ASSERT_TEST( addARoom(system, email, id, price, num_ppl, working_hrs, difficulty) == MTM_ID_ALREADY_EXIST );

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

	ASSERT_TEST( removeARoom(nullSystem, faculty, id) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeARoom(system, invalidFaculty, id) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( removeARoom(system, faculty, invalidId) == MTM_INVALID_PARAMETER );

	ASSERT_TEST( removeARoom(system, faculty, doesNotExistId) == MTM_ID_DOES_NOT_EXIST );
	ASSERT_TEST( removeARoom(system, faculty2, id) == MTM_ID_DOES_NOT_EXIST );

	ASSERT_TEST( removeARoom(system, faculty, id) == MTM_SUCCESS );

	ASSERT_TEST( removeARoom(system, faculty, orderedId) == MTM_RESERVATION_EXISTS );
	ASSERT_TEST( removeARoom(system, faculty, orderedId2) == MTM_RESERVATION_EXISTS );

	destroySystem(system);
	return true;
}




int systemTests () {
	RUN_TEST(testAddACompany);
	RUN_TEST(testRemoveACompany);

	RUN_TEST(testAddARoom);
	RUN_TEST(testRemoveARoom);



	return 0;
}
