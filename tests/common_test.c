/*
 * common_test.c
 *
 *  Created on: Jun 10, 2017
 *      Author: master
 */


#include "common_test.h"



static bool testEmailValidation() {

	ASSERT_TEST( emailValidation("e@") == true );

	ASSERT_TEST( emailValidation("company@civil") == true );
	ASSERT_TEST( emailValidation("company#civil") == false );
	ASSERT_TEST( emailValidation("compan@@civil") == false );
	ASSERT_TEST( emailValidation("") == false );


	return true;
}

static bool testFacultyValidation() {

	ASSERT_TEST( facultyValidation(0) == true );
	ASSERT_TEST( facultyValidation(17) == true );

	ASSERT_TEST( facultyValidation(-1) == false );
	ASSERT_TEST( facultyValidation(18) == false );

	return true;
}

static bool testSkillLevelValidation() {

	ASSERT_TEST( skillLevelValidation(1) == true );
	ASSERT_TEST( skillLevelValidation(10) == true );

	ASSERT_TEST( skillLevelValidation(0) == false );
	ASSERT_TEST( skillLevelValidation(11) == false );
	return true;
}

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

static bool testIdValidation() {

	ASSERT_TEST( idValidation(1) == true );
	ASSERT_TEST( idValidation(0) == false );
	ASSERT_TEST( idValidation(-1) == false );

	return true;
}

static bool testHourValidation() {

	ASSERT_TEST( hourValidation(0) == true );
	ASSERT_TEST( hourValidation(1) == true );
	ASSERT_TEST( hourValidation(23) == true );
	ASSERT_TEST( hourValidation(-1) == false );
	ASSERT_TEST( hourValidation(24) == false );

	return true;
}

static bool testHoursValidation() {

	ASSERT_TEST( hoursValidation(0,24) == true );
	ASSERT_TEST( hoursValidation(22,23) == true );
	ASSERT_TEST( hoursValidation(0,1) == true );
	ASSERT_TEST( hoursValidation(1,0) == false );
	ASSERT_TEST( hoursValidation(20,20) == false );
	ASSERT_TEST( hoursValidation(0,25) == false );
	ASSERT_TEST( hoursValidation(-1,24) == false );

	return true;
}

static bool testPriceValidation() {

	ASSERT_TEST( priceValidation(0) == false );

	ASSERT_TEST( priceValidation(1) == false );

	ASSERT_TEST( priceValidation(4) == true );

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

static bool testConvertDayStringToInt() {

	ASSERT_TEST( convertDayStringToInt("0-12") == 0 );
	ASSERT_TEST( convertDayStringToInt("10-12") == 10 );

	return true;
}


static bool testConvertHourStringToInt() {

	ASSERT_TEST( convertHourStringToInt("0-12") == 12 );
	ASSERT_TEST( convertHourStringToInt("10-0") == 0 );

	return true;
}




static bool testNumberOfPeoplepriceValidation() {

	ASSERT_TEST( numberOfPeoplepriceValidation(-1) == false );
	ASSERT_TEST( numberOfPeoplepriceValidation(0) == false );
	ASSERT_TEST( numberOfPeoplepriceValidation(1) == true );

	return true;
}





int commonTests () {
	printf("\n\n ================ Common Tests ================ \n\n");
	RUN_TEST(testEmailValidation);
	RUN_TEST(testFacultyValidation);
	RUN_TEST(testSkillLevelValidation);
	RUN_TEST(testTimeValidation);
	RUN_TEST(testIdValidation);
	RUN_TEST(testHourValidation);
	RUN_TEST(testHoursValidation);
	RUN_TEST(testNumberOfPeoplepriceValidation);
	RUN_TEST(testConvertDayStringToInt);
	RUN_TEST(testConvertHourStringToInt);



	RUN_TEST(testPriceValidation);
	RUN_TEST(testConvertStringToCommand);


	return 0;
}
