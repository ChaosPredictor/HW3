/*
 * order_test.c
 *
 *  Created on: May 31, 2017
 *      Author: master
 */

#include "./order_test.h"


static bool testCopyOrder() {

	ASSERT_TEST( copyOrder(NULL) == NULL);

	Order order = malloc(sizeof(struct order_t));
	char* email = "qazxsw@edcvfr";
	order->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(order->email, email);

	order->faculty = CIVIL_ENGINEERING;
	order->id = 1;
	order->price = 16;
	order->num_ppl = 5;
	order->hour = 8;

	Order newOrder = copyOrder(order);

	ASSERT_TEST( newOrder != NULL);
	ASSERT_TEST( strcmp(order->email,newOrder->email) == 0);
	ASSERT_TEST( order->id == newOrder->id );
	ASSERT_TEST( order->price == newOrder->price );
	ASSERT_TEST( order->num_ppl == newOrder->num_ppl );
	ASSERT_TEST( order->hour == newOrder->hour );

	free(newOrder->email);
	free(newOrder);

	free(order->email);
	free(order);

	return true;
}

static bool testFreeOrder() {

	//ASSERT_TEST( freeOrder(NULL) == NULL);
	freeOrder(NULL);

	Order order = malloc(sizeof(struct order_t));
	char* email = "qazxsw@edcvfr";
	order->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(order->email, email);
	order->faculty = CIVIL_ENGINEERING;
	order->id = 1;
	order->price = 16;
	order->num_ppl = 5;
	order->hour = 8;

	Order newOrder = copyOrder(order);

	freeOrder(newOrder);
	freeOrder(order);

	return true;
}


static bool testAddOrder() {

	//TODO create list of days;
	//List days = listCreate(copyDay, freeDay);
	List days = createDays();
	Set users = testHelperAddUsers();
	Set rooms = testHelperAddRooms(users);

	int numberOfOrders = 0;
	int numberOfDays = 0;


	TechnionFaculty faculty = MECHANICAL_ENGINEERING;
	int id = 1;

	Day firstDay = listGetFirst(days);

	//printf("\nfirst day today: %d \n", firstDay->day);

	//fail - email
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1#civil", faculty, id, "1-6", 3) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper7@civil", faculty, id, "1-6", 3) == MTM_CLIENT_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	//fail - faculty&id doesn't exist
	id = 7;
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@civil", faculty, id, "1-6", 3) == MTM_ID_DOES_NOT_EXIST );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	id = 1;
	//fail - working hours
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@civil", faculty, id, "1-3", 3) == MTM_ROOM_NOT_AVAILABLE );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@civil", faculty, id, "1-20", 3) == MTM_ROOM_NOT_AVAILABLE );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	//TODO to ask if it's should work
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@civil", faculty, id, "1-7", 3) == MTM_ROOM_NOT_AVAILABLE );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );


	//success - add to first day
	//printf("case1\n");
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@civil", faculty, id, "0-6", 3) == MTM_SUCCESS );
	numberOfOrders++;
	numberOfDays++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	Order order = listGetFirst(firstDay->dayOrders);
	ASSERT_TEST( order->price == getRoomPrice(rooms, faculty, id) );


	//fail - escaper have other order same time
	//printf("case2\n");
	faculty = CIVIL_ENGINEERING;
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	//printf("case2 %d\n", addOrder(days, users, rooms, "escaper1@civil", faculty, id, "0-6", 3));

	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@civil", faculty, id, "0-6", 3) == MTM_CLIENT_IN_ROOM );
	//numberOfOrders++;
	//numberOfDays++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );



	//success - add to not exist day
	//printf("case2\n");
	faculty = MECHANICAL_ENGINEERING;
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@civil", faculty, id, "5-6", 3) == MTM_SUCCESS );
	//numberOfOrders++;
	numberOfDays++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	order = listGetFirst(firstDay->dayOrders);
	ASSERT_TEST( order->price == getRoomPrice(rooms, faculty, id) );

	//success - add to first day again
	//printf("case3\n");
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@mechanical", faculty, id, "0-6", 3) == MTM_SUCCESS );
	numberOfOrders++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	List orders = firstDay->dayOrders;
	order = listGetFirst(orders);
	ASSERT_TEST( order->price == getRoomPrice(rooms, faculty, id) * 75 / 100 );

	//success - add to not exist day in the middle
	//printf("case4\n");
	faculty = ELECTRICAL_ENGINEERING;
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper1@civil", faculty, id, "3-6", 3) == MTM_SUCCESS );
	//numberOfOrders++;
	numberOfDays++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	listGetFirst(days);
	Day day = listGetNext(days);
	order = listGetFirst(day->dayOrders);
	ASSERT_TEST( order->price == getRoomPrice(rooms, faculty, id) );

	//success - add to exist day in the middle
	//printf("case5\n");
	id = 2;
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper2@civil", faculty, id, "3-6", 3) == MTM_SUCCESS );
	//numberOfOrders++;
	//numberOfDays++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	listGetFirst(days);
	day = listGetNext(days);
	order = listGetFirst(day->dayOrders);
	ASSERT_TEST( order->price == getRoomPrice(rooms, faculty, id) );


	id = 2;
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper2@civil", faculty, id, "7-6", 3) == MTM_SUCCESS );
	//numberOfOrders++;
	numberOfDays++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	listGetFirst(days);
	day = listGetNext(days);
	order = listGetFirst(day->dayOrders);
	ASSERT_TEST( order->price == getRoomPrice(rooms, faculty, id) );


	id = 2;
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper2@civil", faculty, id, "2-6", 3) == MTM_SUCCESS );
	//numberOfOrders++;
	numberOfDays++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	listGetFirst(days);
	day = listGetNext(days);
	order = listGetFirst(day->dayOrders);
	ASSERT_TEST( order->price == getRoomPrice(rooms, faculty, id) );

	id = 2;
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	ASSERT_TEST( addOrder(days, users, rooms, "escaper2@civil", faculty, id, "6-6", 3) == MTM_SUCCESS );
	//numberOfOrders++;
	numberOfDays++;
	ASSERT_TEST( listGetSize(days) == numberOfDays );
	ASSERT_TEST( listGetSize(firstDay->dayOrders) == numberOfOrders );
	listGetFirst(days);
	day = listGetNext(days);
	order = listGetFirst(day->dayOrders);
	ASSERT_TEST( order->price == getRoomPrice(rooms, faculty, id) );

	printAllDays(days);


	setDestroy(rooms);
	setDestroy(users);
	listDestroy(days);
	return true;
}


static bool testAddOrderToADay() {

/*	List days = listCreate(copyDay, freeDay);
	addToday(days);
	*/
	List days = createDays();

	Day day = listGetFirst(days);
	List orders = day->dayOrders;

	//rooms set, users set or email is NULL
	ASSERT_TEST( addOrderToADay(NULL, "escaper1@civil", MECHANICAL_ENGINEERING, 1, 5, 6, 3) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( listGetSize(orders) == 0 );
	ASSERT_TEST( addOrderToADay(orders, NULL, MECHANICAL_ENGINEERING, 1, 5, 6, 3) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( listGetSize(orders) == 0 );


	ASSERT_TEST( addOrderToADay(orders, "escaper1@civil", MECHANICAL_ENGINEERING, 1, 5, 6, 3) == MTM_SUCCESS );
	ASSERT_TEST( listGetSize(orders) == 1 );
	ASSERT_TEST( addOrderToADay(orders, "escaper1@civil", MECHANICAL_ENGINEERING, 1, 5, 6, 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper2@civil", MECHANICAL_ENGINEERING, 4, 5, 8, 6) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper3@civil", MECHANICAL_ENGINEERING, 6, 5, 5, 8) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper4@civil", MECHANICAL_ENGINEERING, 2, 5, 10, 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper5@civil", MECHANICAL_ENGINEERING, 1, 5, 12, 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper1@mechanical", MECHANICAL_ENGINEERING, 1, 5, 6, 8) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper1@mechanical", MECHANICAL_ENGINEERING, 1, 5, 6, 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper1@mechanical", MECHANICAL_ENGINEERING, 1, 5, 6, 3) == MTM_SUCCESS );

	listDestroy(days);
	//printf("\nnumber of days: %d\n", listGetSize(days));

	return true;
}

/*
static List testHelperAddOrderToADay() {

	List orders = listCreate(copyOrder ,freeOrder);
	ASSERT_TEST( orders != NULL);
	ASSERT_TEST( addOrderToADay(orders, "escaper1@civil", MECHANICAL_ENGINEERING, 1, 6, 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper2@civil", MECHANICAL_ENGINEERING, 4, 8, 6) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper3@civil", MECHANICAL_ENGINEERING, 6, 5, 8) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper4@civil", MECHANICAL_ENGINEERING, 2, 10, 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper5@civil", MECHANICAL_ENGINEERING, 1, 12, 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper1@mechanical", MECHANICAL_ENGINEERING, 1, 6, 8) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper1@mechanical", MECHANICAL_ENGINEERING, 1, 6, 3) == MTM_SUCCESS );
	ASSERT_TEST( addOrderToADay(orders, "escaper1@mechanical", MECHANICAL_ENGINEERING, 1, 6, 3) == MTM_SUCCESS );

}*/



static bool testCopyDay() {

	//TODO

	return true;
}

int orderTests (int argv, char** arc) {
//int main (int argv, char** arc) {
	RUN_TEST(testCopyOrder);
	RUN_TEST(testFreeOrder);
	RUN_TEST(testAddOrder);
	RUN_TEST(testAddOrderToADay);

	RUN_TEST(testCopyDay);

	/*RUN_TEST(testCompareRoom);
	RUN_TEST(testRemoveRoom);
	RUN_TEST(testOtherSetRoomFunctions);*/

	return 0;
}
