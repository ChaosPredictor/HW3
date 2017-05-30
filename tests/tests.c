/*
 * tests.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */

#include "company_test.c"
#include "room_test.c"

int main(int argv, char** arc) {
	companyTests(argv, arc);
	roomTests(argv, arc);
}
