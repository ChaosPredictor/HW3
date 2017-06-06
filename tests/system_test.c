/*
 * system_test.c
 *
 *  Created on: Jun 6, 2017
 *      Author: master
 */


#include "./system_test.h"



Set testHelperUsers() {
	Set users = setCreate(copyUser, freeUser, compareUsers);
	ASSERT_TEST( users != NULL);

	addUser( users, "company1@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company2@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company3@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company5@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company1@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company2@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company3@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company4@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company6@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company2@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company3@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company5@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company6@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company7@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@chemical", CHEMICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@biotechnology", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, COMPANY );
	addUser( users, "company1@aerospace", AEROSPACE_ENGINEERING, COMPANY );
	addUser( users, "company1@industrial", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT, COMPANY );
	addUser( users, "company1@mathematics", MATHEMATICS, COMPANY );
	addUser( users, "company1@physics", PHYSICS, COMPANY );
	addUser( users, "company1@chemistry", CHEMISTRY, COMPANY );
	addUser( users, "company1@biology", BIOLOGY, COMPANY );
	addUser( users, "company1@architecture", ARCHITECTURE, COMPANY );
	addUser( users, "company1@education", EDUCATION_IN_TECH_AND_SCIENCE, COMPANY );
	addUser( users, "company1@computer", COMPUTER_SCIENCE, COMPANY );
	addUser( users, "company1@medicine", MEDICINE, COMPANY );
	addUser( users, "company1@materials", MATERIALS_ENGINEERING, COMPANY );
	addUser( users, "company1@humanites", HUMANITIES_AND_ARTS, COMPANY );
	addUser( users, "company1@biomedical", BIOMEDICAL_ENGINEERING, COMPANY );
	addUser( users, "escaper1@civil", CIVIL_ENGINEERING, ESCAPER_1 );
	addUser( users, "escaper2@civil", CIVIL_ENGINEERING, ESCAPER_5 );
	addUser( users, "escaper3@mechanical", MECHANICAL_ENGINEERING, ESCAPER_2 );
	addUser( users, "escaper1@mechanical", MECHANICAL_ENGINEERING, ESCAPER_8 );
	addUser( users, "escaper1@electrical", ELECTRICAL_ENGINEERING, ESCAPER_10 );
	addUser( users, "escaper2@electrical", ELECTRICAL_ENGINEERING, ESCAPER_6 );
	addUser( users, "escaper1@physics", PHYSICS, ESCAPER_6 );
	addUser( users, "escaper1@biotechnology", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, ESCAPER_1 );
	addUser( users, "escaper1@aerospace", AEROSPACE_ENGINEERING, ESCAPER_7 );
	addUser( users, "escaper1@education", EDUCATION_IN_TECH_AND_SCIENCE, ESCAPER_9 );
	addUser( users, "escaper1@mathematics", MATHEMATICS, ESCAPER_7 );


	ASSERT_TEST( setGetSize(users) == 41 );
	return users;
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
