/*
 * tests.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */

#include "company_test.h"
#include "system_test.h"
#include "common_test.h"


//int main2(int argv, char** arc) {
int main() {
	//userTests(argv, arc);
	//roomTests(argv, arc);
	//orderTests(argv, arc);
	companyTests();
	commonTests();
	systemTests();
	return 1;
}
