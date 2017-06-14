/*
 * common.h
 *
 *  Created on: Jun 9, 2017
 *      Author: master
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "mtm_ex3.h"


typedef enum {
	ESCAPER_1,
	ESCAPER_2,
	ESCAPER_3,
	ESCAPER_4,
	ESCAPER_5,
	ESCAPER_6,
	ESCAPER_7,
	ESCAPER_8,
	ESCAPER_9,
	ESCAPER_10
} SkillLevel;


#define NUMBER_OF_FACULTIES UNKNOWN


bool emailValidation(const char* email);

bool facultyValidation(TechnionFaculty faculty);

bool skillLevelValidation(SkillLevel skill_level);

bool timeValidation(const char* time);

bool idValidation(int id);

bool hourValidation (int hour);

bool hoursValidation (int from, int to);

bool priceValidation (int price);

bool numberOfPeoplepriceValidation (int num_ppl);


int convertDayStringToInt(const char* time );

int convertHourStringToInt(const char* time );

int convertStringToCommand( const char* line );

int fromHour(const char* working_hrs);

int toHour(const char* working_hrs);

int charToInt(char c);

#endif /* COMMON_H_ */
