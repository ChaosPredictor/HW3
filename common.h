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

/* check email validity
 * @param
 * 	email - email to check
 * @return
 *	true - email is valid
 *	false - otherwise
 */
bool emailValidation(const char* email);

/* check faculty validity
 * @param
 * 	faculty - faculty to check
 * @return
 *	true - faculty is valid
 *	false - otherwise
 */
bool facultyValidation(TechnionFaculty faculty);

/* check skill level validity
 * @param
 * 	skill_level - skill level to check
 * @return
 *	true - skill level is valid
 *	false - otherwise
 */
bool skillLevelValidation(SkillLevel skill_level);

/* check time validity
 * @param
 * 	time - time to check
 * @return
 *	true - time is valid
 *	false - otherwise
 */
bool timeValidation(const char* time);

/* check id validity
 * @param
 * 	id - id to check
 * @return
 *	true - id is valid
 *	false - otherwise
 */
bool idValidation(int id);

/* check hour validity
 * @param
 * 	hour - hour to check
 * @return
 *	true - hour is valid
 *	false - otherwise
 */
bool hourValidation (int hour);

/* check hours validity
 * @param
 * 	hours - hours to check (from and to)
 * @return
 *	true - hour is valid
 *	false - otherwise
 */
bool hoursValidation (int from, int to);

/* check price validity
 * @param
 * 	price - price to check
 * @return
 *	true - price is valid
 *	false - otherwise
 */
bool priceValidation (int price);

/* check number of people validity
 * @param
 * 	num_ppl - number of people to check
 * @return
 *	true - number of people is valid
 *	false - otherwise
 */
bool numberOfPeoplepriceValidation (int num_ppl);

/* return day from time string
 * @param
 * 	time - time input to convert
 * @return
 * 	number - day of time input
 */
int convertDayStringToInt(const char* time );

/* return hour from time string
 * @param
 * 	time - time input to convert
 * @return
 * 	number - hour of time input
 */
int convertHourStringToInt(const char* time );

/* return command number from command line
 * @param
 * 	line - line from input
 * @return
 * 	number - command:
 * 		0 - not a legal command
 * 		1 - company add
 * 		2 - company remove
 * 		3 - room add
 * 		4 - room remove
 * 		5 - escape add
 * 		6 - escape remove
 * 		7 - escape order
 * 		8 - escaper recommend
 * 		9 - report day
 * 		10 -report best
 */
int convertStringToCommand(const char* line );

/* return from hour from working time string
 * @param
 * 	working_hrs - working_hrs input to convert
 * @return
 * 	number - from hour of time input
 */
int fromHour(const char* time);

/* return from hour from working time string
 * @param
 * 	working_hrs - working_hrs input to convert
 * @return
 * 	number - to hour of time input
 */
int toHour(const char* time);

/* return int from number char
 * @param
 * 	number_char - char that include a number
 * @return
 * 	number - number value of the char
 */
int charToInt(char number_char);

#endif /* COMMON_H_ */
