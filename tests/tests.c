/*
 * tests.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */

#include "room_test.h"
#include "user_test.h"
#include "order_test.h"
#include "system_test.h"


int main2(int argv, char** arc) {
	userTests(argv, arc);
	roomTests(argv, arc);
	orderTests(argv, arc);
	systemTests(argv, arc);
	return 1;
}
