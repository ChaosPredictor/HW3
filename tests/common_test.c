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

static bool testPriceValidation() {

	ASSERT_TEST( priceValidation(0) == false );

	return true;
}

static bool testConvertStringToCommand() {

	ASSERT_TEST( convertStringToCommand( "#" ) == 0 );
	ASSERT_TEST( convertStringToCommand( "				#NANANANANANA BATMAN! company add you" ) == 0 );
	ASSERT_TEST( convertStringToCommand( "		 	" ) == 0 );
	ASSERT_TEST( convertStringToCommand( "#bad" ) == 0 );
	ASSERT_TEST( convertStringToCommand( "#zzzzzzzzz" ) == 0 );
	ASSERT_TEST( convertStringToCommand( "#nothing to report" ) == 0 );
	//printf("\n\n%d\n\n", convertStringToCommand( "company add company1@gmail 0" ) );
	ASSERT_TEST( convertStringToCommand( "company add company1@gmail 0" ) == 1 );

	ASSERT_TEST( convertStringToCommand( "	room	 add	 company1@gmail 	1 		100 	4 	00-24	 9 " ) == 3 );
	ASSERT_TEST( convertStringToCommand( "room		 add company3@gmail 1 40 4 04-05 10" ) == 3 );
	ASSERT_TEST( convertStringToCommand( "		room add company5@gmail 8 60 2 08-09 2" ) == 3 );

	ASSERT_TEST( convertStringToCommand( "escaper add company3@gmail 0 0" ) == 5 );
	ASSERT_TEST( convertStringToCommand( "          escaper add company3@gmail 0 0" ) == 5 );

	ASSERT_TEST( convertStringToCommand( "	escaper order 0@ 0 123 0-10 4" ) == 7 );
	ASSERT_TEST( convertStringToCommand( "escaper	 order 5@ 16 8 0-08 5" ) == 7 );

	ASSERT_TEST( convertStringToCommand( "report day" ) == 9 );
	ASSERT_TEST( convertStringToCommand( "report day " ) == 9 );
	ASSERT_TEST( convertStringToCommand( "report day" ) == 9 );

	return true;
}




int commonTests () {
	RUN_TEST(testTimeValidation);
	RUN_TEST(testPriceValidation);
	RUN_TEST(testConvertStringToCommand);


	return 0;
}
