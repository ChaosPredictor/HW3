/*
 * order_test.c
 *
 *  Created on: May 31, 2017
 *      Author: master
 */





int orderTests (int argv, char** arc) {
//int main (int argv, char** arc) {
	RUN_TEST(testCopyOrder);
	RUN_TEST(testFreeOrder);
	/*RUN_TEST(testCompareRoom);
	RUN_TEST(testAddRoom);
	RUN_TEST(testRemoveRoom);
	RUN_TEST(testOtherSetRoomFunctions);*/

	return 0;
}
