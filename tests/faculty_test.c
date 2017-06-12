/*
 * faculty_test.c
 *
 *  Created on: Jun 12, 2017
 *      Author: master
 */

#include "faculty_test.h"


static bool testCopyFaculty() {

	ASSERT_TEST( copyFaculty(NULL) == NULL);

	Faculty faculty = malloc(sizeof(struct faculty_t));

	faculty->id = 10;
	faculty->income = 555;

	Faculty newFaculty = copyFaculty(faculty);

	ASSERT_TEST( newFaculty != NULL);
	ASSERT_TEST( faculty->id == newFaculty->id );
	ASSERT_TEST( faculty->income == newFaculty->income );


	free(newFaculty);
	free(faculty);

	return true;
}

static bool testFreeFaculty() {

	freeFaculty(NULL);

	Faculty faculty = malloc(sizeof(struct faculty_t));
	faculty->id = 0;
	faculty->income = 333;

	Faculty newFaculty = copyFaculty(faculty);

	freeFaculty(newFaculty);
	freeFaculty(faculty);

	return true;
}

static bool testCompareFacultyByIncomeAndId() {

	Faculty faculty1 = malloc(sizeof(struct faculty_t));
	Faculty faculty2 = malloc(sizeof(struct faculty_t));
	Faculty faculty3 = malloc(sizeof(struct faculty_t));


	faculty1->id = 10;
	faculty1->income = 555;
	faculty2->id = 10;
	faculty2->income = 334;
	faculty3->id = 1;
	faculty3->income = 555;


	ASSERT_TEST( compareFacultyByIncomeAndId(faculty1, faculty2) < 0);
	ASSERT_TEST( compareFacultyByIncomeAndId(faculty2, faculty3) > 0);
	ASSERT_TEST( compareFacultyByIncomeAndId(faculty1, faculty3) > 0);
	free(faculty1);
	free(faculty2);
	free(faculty3);

	return true;
}


static bool testAddIncomeToFaculty() {

	Faculty faculty = malloc(sizeof(struct faculty_t));


	faculty->id = 10;
	faculty->income = 555;

	ASSERT_TEST( addIncomeToFaculty(faculty, 10) == MTM_SUCCESS );
	ASSERT_TEST( faculty->income == 565 );

	free(faculty);
	return true;
}






int facultyTests () {
	printf("\n\n ================ Faculty Tests ================ \n\n");
	RUN_TEST(testCopyFaculty);
	RUN_TEST(testFreeFaculty);
	RUN_TEST(testCompareFacultyByIncomeAndId);
	RUN_TEST(testAddIncomeToFaculty);

	return 0;
}
