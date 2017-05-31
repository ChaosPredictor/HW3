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



int orderTests (int argv, char** arc) {
//int main (int argv, char** arc) {
	RUN_TEST(testCopyOrder);
	//RUN_TEST(testFreeOrder);
	/*RUN_TEST(testCompareRoom);
	RUN_TEST(testAddRoom);
	RUN_TEST(testRemoveRoom);
	RUN_TEST(testOtherSetRoomFunctions);*/

	return 0;
}
