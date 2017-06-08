/*
 * user_test.h
 *
 *  Created on: May 31, 2017
 *      Author: master
 */

#ifndef TESTS_USER_TEST_H_
#define TESTS_USER_TEST_H_



//#include "./../user.c"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
//#include "./../mtm_escape.h"
#include <string.h>
#include <ctype.h>
#include "../escaper.h"
#include "./test_utilities.h"


Set testHelperAddUsers();

/*
static bool testCopyUser();

static bool testFreeUser();

static bool testCompareUser();

static bool testAddUser();

static bool testRemoveCompany();

static bool testFindFacultyFromEmail();

static bool testEmailValidity();

static bool testOtherSetUserFunctions();
*/

int userTests (int argv, char** arc);



#endif /* TESTS_USER_TEST_H_ */
