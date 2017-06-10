/*
 * common.c
 *
 *  Created on: Jun 9, 2017
 *      Author: master
 */


#include "common.h"




bool emailValidity(const char* email) {
	if ( email == NULL ) return false;
	size_t len = strlen(email);
	int count = 0;
	for (int i = 0; i < len; i++) {
		if( email[i] == '@' ) count++;
	}
	return ( count == 1);
}

bool facultyValidity(TechnionFaculty faculty) {
	if ( faculty < 0 || faculty >= NUMBER_OF_FACULTIES ) {
		return false;
	}
	return true;
}

bool skillLevelValidation(SkillLevel skillLevel) {
	if ( skillLevel < ESCAPER_1 || skillLevel > ESCAPER_10 ) return false;
	return true;
}

bool timeValidation(const char* time) {
	if ( time == NULL ) return false;
	size_t len = strlen(time);
	if ( time[0] < '0' || time[0] > '9' ) return false;
	if ( time[1] != '-' && time[2] != '-' ) return false;
	if ( time[len-1] < '0' || time[len-1] > '9' ) return false;
	int day = convertDayStringToInt( time );
	if ( day < 0 || day > 10 ) return false;
	int hour = convertHourStringToInt( time );
	if ( hour < 0 || hour > 23 ) return false;
	return true;
}

bool idValidation(int id) {
	if ( id > 0 ) return true;
	return false;
}






int convertDayStringToInt( const char* time ) {
	char *temp = malloc(sizeof(char) * (strlen(time) + 1));
	strcpy(temp,time);
	int daysFromToday = atoi( strtok(temp, "-") );
	free( temp );
	return daysFromToday;
}

int convertHourStringToInt( const char* time ) {
	char *temp = malloc(sizeof(char) * (strlen(time) + 1));
	strcpy(temp,time);
	atoi( strtok(temp, "-") );
	int hour = atoi( strtok(NULL, "-") );
	free( temp );
	return hour;
}
