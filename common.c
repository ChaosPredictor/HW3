/*
 * common.c
 *
 *  Created on: Jun 9, 2017
 *      Author: master
 */


#include "common.h"


#define MAX_DAYS_AHEAD 10
#define LAST_HOUR_ADAY 23

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
	if ( day < 0 || day > MAX_DAYS_AHEAD ) return false;
	int hour = convertHourStringToInt( time );
	if ( hour < 0 || hour > LAST_HOUR_ADAY ) return false;
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



int convertStringToCommand( const char* line ) {
	char *temp = malloc(sizeof(char) * (strlen(line) + 1));
	strcpy(temp,line);
	char* command = strtok(temp, " \t");
	if ( command == NULL || command[0] == '#' ) {
		free(temp);
		return 0;
	}
	while(isspace((unsigned char)*command)) command++;
	char* subcommand = strtok(NULL, " \t");
	while(isspace((unsigned char)*subcommand)) subcommand++;
	int result = 0;

	if ( strcmp(command, "company" ) == 0 ) {
		if ( strcmp(subcommand, "add" ) == 0 ) {
			result = 1;
		} else if ( strcmp(subcommand, "remove" ) == 0 ) {
			result = 2;
		}
	} else if ( strcmp(command, "room" ) == 0 ) {
		if ( strcmp(subcommand, "add" ) == 0 ) {
			result = 3;
		} else if ( strcmp(subcommand, "remove" ) == 0 ) {
			result = 4;
		}
	} else if ( strcmp(command, "escaper" ) == 0 ) {
		if ( strcmp(subcommand, "add" ) == 0 ) {
			result = 5;
		} else if ( strcmp(subcommand, "remove" ) == 0 ) {
			result = 6;
		} else if ( strcmp(subcommand, "order" ) == 0 ) {
			result = 7;
		} else if ( strcmp(subcommand, "recommend" ) == 0 ) {
			result = 8;
		}
	} else if ( strcmp(command, "report" ) == 0 ) {
		if ( strcmp(subcommand, "day\n" ) == 0 || strcmp(subcommand, "day\0" ) == 0) {
			result = 9;
		} else if ( strcmp(subcommand, "best\n" ) == 0 || strcmp(subcommand, "best\0" ) == 0 ) {
			result = 10;
		}
	}
	free( temp );
	return result;
}