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
	order->day = 2;
	order->hour = 8;

	Order newOrder = copyOrder(order);

	ASSERT_TEST( newOrder != NULL);
	ASSERT_TEST( strcmp(order->email,newOrder->email) == 0);
	ASSERT_TEST( order->id == newOrder->id );
	ASSERT_TEST( order->price == newOrder->price );
	ASSERT_TEST( order->num_ppl == newOrder->num_ppl );
	ASSERT_TEST( order->day == newOrder->day );
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
	order->day = 2;
	order->hour = 8;

	Order newOrder = copyOrder(order);

	freeOrder(newOrder);
	freeOrder(order);

	return true;
}


static bool testAddOrder() {

	List orders = listCreate(copyOrder ,freeOrder);
	ASSERT_TEST( orders != NULL);

	ASSERT_TEST( addOrder(orders, "escaper1@civil", MECHANICAL_ENGINEERING, 1, "0-6", 3) == MTM_SUCCESS );
	ASSERT_TEST( listGetSize(orders) == 1 );


/*

	//rooms set, users set or email is NULL
	ASSERT_TEST( addRoom(NULL, users, "company1@civil", 1, 4, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, NULL, "company1@civil", 1, 4, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, NULL, 1, 4, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//illegal email
	ASSERT_TEST( addRoom(rooms, users, "company1#civil", 1, 4, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//company email does not exist
	ASSERT_TEST( addRoom(rooms, users, "company5@civil", 1, 4, 3, "05-07", 10) == MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "escaper1@civil", 1, 4, 3, "05-07", 10) == MTM_COMPANY_EMAIL_DOES_NOT_EXIST );
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//0 & -1 id
	ASSERT_TEST( addRoom(rooms, users, "company1@civil",0, 4, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "company1@civil",-1, 4, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//price
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 0, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, -1, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 9, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//num_ppl
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 0, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, -1, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//working hours
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "07-05", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "05-05", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "05-24", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "24-05", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//difficulty
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "05-07", 0) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "05-07", 11) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 0 );
	//pass
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "05-07", 10) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(rooms) == 1 );
	//fail - same company same id
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "05-07", 10) == MTM_ID_ALREADY_EXIST );
	ASSERT_TEST( setGetSize(rooms) == 1 );

	//pass - same faculty, different id
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 2, 4, 3, "05-07", 10) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(rooms) == 2 );

	//pass - same id, different faculty
	ASSERT_TEST( addRoom(rooms, users, "company1@mechanical", 1, 4, 3, "05-07", 10) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(rooms) == 3 );

	//fail - different company same id
	ASSERT_TEST( addRoom(rooms, users, "company2@civil", 1, 4, 3, "05-07", 10) == MTM_ID_ALREADY_EXIST );
	ASSERT_TEST( setGetSize(rooms) == 3 );

	setClear(rooms);

	ASSERT_TEST( setGetSize(rooms) == 0 );
*/
	listDestroy(orders);
	return true;
}

int orderTests (int argv, char** arc) {
//int main (int argv, char** arc) {
	RUN_TEST(testCopyOrder);
	RUN_TEST(testFreeOrder);
	RUN_TEST(testAddOrder);

	/*RUN_TEST(testCompareRoom);
	RUN_TEST(testRemoveRoom);
	RUN_TEST(testOtherSetRoomFunctions);*/

	return 0;
}
