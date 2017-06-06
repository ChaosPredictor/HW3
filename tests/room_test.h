/*
 * room_test.h
 *
 *  Created on: May 31, 2017
 *      Author: master
 */

#ifndef TESTS_ROOM_TEST_H_
#define TESTS_ROOM_TEST_H_

#include "./test_utilities.h"
#include "./user_test.h"
//#include "./../mtm_escape.h"
//#include "./../room.c"
#include "./../room.h"
#include "./../user.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int roomTests (int argv, char** arc);

Set testHelperAddRooms(Set users);

#endif /* TESTS_ROOM_TEST_H_ */
