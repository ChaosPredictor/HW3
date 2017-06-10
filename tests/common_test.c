/*
 * common_test.c
 *
 *  Created on: Jun 10, 2017
 *      Author: master
 */


#include "common_test.h"


static bool testTimeValidation() {

	ASSERT_TEST( timeValidation("0-0") == true );
	ASSERT_TEST( timeValidation("0-1") == true );
	ASSERT_TEST( timeValidation("0-23") == true );
	ASSERT_TEST( timeValidation("5-12") == true );
	ASSERT_TEST( timeValidation("10-0") == true );
	ASSERT_TEST( timeValidation("10-1") == true );
	ASSERT_TEST( timeValidation("10-23") == true );

	ASSERT_TEST( timeValidation(NULL) == false );
	ASSERT_TEST( timeValidation("") == false );

	ASSERT_TEST( timeValidation("5-24") == false );
	ASSERT_TEST( timeValidation("11-1") == false );

	ASSERT_TEST( timeValidation("5_12") == false );
	ASSERT_TEST( timeValidation("5 12") == false );
	ASSERT_TEST( timeValidation("5&12") == false );
	ASSERT_TEST( timeValidation("5*12") == false );

	ASSERT_TEST( timeValidation("x-1") == false );
	ASSERT_TEST( timeValidation("X-1") == false );
	ASSERT_TEST( timeValidation("0-x") == false );
	ASSERT_TEST( timeValidation("0-X") == false );



	return true;
}





int commonTests () {
	RUN_TEST(testTimeValidation);


	return 0;
}
