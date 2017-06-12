/*
 * order_test.c
 *
 *  Created on: May 31, 2017
 *      Author: master
 */

#include "./order_test.h"



static bool testCopyDay() {

	ASSERT_TEST( copyOrder(NULL) == NULL);

	Day day = malloc(sizeof(struct day_t));
	day->dayNumber = 0;
	day->dayOrders = listCreate(copyOrder ,freeOrder);


	Day newDay = copyDay(day);

	ASSERT_TEST( newDay != NULL);
	ASSERT_TEST( day->dayNumber == newDay->dayNumber );
	ASSERT_TEST( listGetSize(day->dayOrders)==listGetSize(newDay->dayOrders) );

	freeDay(newDay);
	freeDay(day);

	return true;
}

static bool testFreeDay() {

	Day day = malloc(sizeof(struct day_t));
	day->dayNumber = 0;
	day->dayOrders = listCreate(copyOrder ,freeOrder);


	freeDay(day);
	return true;
}

static bool testCreateDay() {

	Day day = createDay(0);

	ASSERT_TEST( day->dayNumber == 0 );
	ASSERT_TEST( day->dayOrders != NULL );

	Day day2 = createDay(6);

	ASSERT_TEST( day2->dayNumber == 6 );
	ASSERT_TEST( day2->dayOrders != NULL );
	freeDay(day2);
	freeDay(day);
	return true;
}

static bool testCreateDays() {

	List days = createDays();

	Day day = listGetFirst(days);

	ASSERT_TEST( day->dayNumber == 0 );
	ASSERT_TEST( day->dayOrders != NULL );


	listDestroy(days);
	return true;
}



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

static bool testCreateOrder() {

	Order order = malloc(sizeof(struct order_t));

	char* email = "escaper1@civil";
	order->faculty = CIVIL_ENGINEERING;
	order->id = 1;
	order->price = 16;
	order->num_ppl = 5;
	order->hour = 8;

	ASSERT_TEST( createOrder(order, email, 20, 1, 20, 3, 12 ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( createOrder(order, email, 0, 0, 20, 3, 12 ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( createOrder(order, email, 0, 1, 20, 0, 12 ) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( createOrder(order, email, 0, 1, 20, 3, 24 ) == MTM_INVALID_PARAMETER );

	ASSERT_TEST( createOrder(order, email, 0, 1, 20, 3, 12 ) == MTM_SUCCESS );

	freeOrder(order);

	return true;
}

static bool testSetOrderHour() {



	Order order = malloc(sizeof(struct order_t));

	char* email = "escaper1@civil";
	order->faculty = CIVIL_ENGINEERING;
	order->id = 1;
	order->price = 16;
	order->num_ppl = 5;
	order->hour = 8;

	ASSERT_TEST( createOrder(order, email, 0, 1, 20, 3, 12 ) == MTM_SUCCESS );
	ASSERT_TEST( setOrderHour(order, 24 ) == MTM_INVALID_PARAMETER );

	ASSERT_TEST( order->hour == 12 );

	ASSERT_TEST( setOrderHour(order, 8 ) == MTM_SUCCESS );

	ASSERT_TEST( order->hour == 8 );

	freeOrder(order);
	return true;
}




int orderTests () {
	printf("\n\n ================ Order Tests ================ \n\n");

	RUN_TEST(testCopyDay);
	RUN_TEST(testFreeDay);
	RUN_TEST(testCreateDay);
	RUN_TEST(testCreateDays);

	RUN_TEST(testCopyOrder);
	RUN_TEST(testFreeOrder);
	RUN_TEST(testCreateOrder);
	RUN_TEST(testSetOrderHour);

	return 0;
}
