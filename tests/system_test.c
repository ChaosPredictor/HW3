/*
 * system_test.c
 *
 *  Created on: Jun 6, 2017
 *      Author: master
 */


#include "./system_test.h"



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




int systemTests (int argv, char** arc) {
	//RUN_TEST(testReportDay);

	return 0;
}
