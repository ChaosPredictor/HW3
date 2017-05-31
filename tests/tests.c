/*
 * tests.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */

#include "room_test.h"
#include "user_test.h"

int main(int argv, char** arc) {
	userTests(argv, arc);
	roomTests(argv, arc);
}
