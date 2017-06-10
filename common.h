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


bool emailValidity(const char* email);

bool facultyValidity(TechnionFaculty faculty);

bool skillLevelValidation(SkillLevel skillLevel);

bool timeValidation(const char* time);

bool idValidation(int id);

int convertDayStringToInt(const char* time );

int convertHourStringToInt(const char* time );


#endif /* COMMON_H_ */
