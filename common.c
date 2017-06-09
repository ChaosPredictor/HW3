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
