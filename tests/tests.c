/*
 * tests.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */


#include "common_test.h"
#include "faculty_test.h"
#include "company_test.h"
#include "room_test.h"
#include "escaper_test.h"
#include "order_test.h"
#include "system_test.h"



//int main2(int argv, char** arc) {
int main() {
	//userTests(argv, arc);
	//roomTests(argv, arc);
	commonTests();
	facultyTests();
	companyTests();
	roomTests();
	escaperTests();
	orderTests();


	systemTests();
	return 1;
}
