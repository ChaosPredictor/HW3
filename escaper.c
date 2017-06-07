/*
 * company.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#include "escaper.h"


//TODO all mails together



SetElement copyEscaper(SetElement escaper) {
	if ( escaper == NULL ) return NULL;
	assert(escaper);
	Escaper newEscaper = malloc(sizeof(struct escaper_t));
	if ( newEscaper == NULL) return MTM_OUT_OF_MEMORY;

	newEscaper->email = malloc(sizeof(char) * (strlen(((Escaper)escaper)->email) + 1));
	if ( newEscaper == NULL) {
		free( newEscaper );
		return MTM_OUT_OF_MEMORY;
	}

	strcpy(newEscaper->email, ((Escaper)escaper)->email);
	newEscaper->typeSkill = ((Escaper)escaper)->typeSkill;
	newEscaper->faculty = ((Escaper)escaper)->faculty;

	return newEscaper;
}

void freeEscaper(SetElement escaper) {
	if ( escaper == NULL ) return;
	//Company tempCompany = (Company)company;
	//printf("email of Company4:%s\n", ((Company)company)->email);
	//char* temp = (((Company)company)->email);
	free(((Escaper)escaper)->email);
	free((Escaper)escaper);
}

int compareEscapers(SetElement escaper1, SetElement escaper2) {
	return strcmp(((Escaper)escaper1)->email, ((Escaper)escaper2)->email);
}




MtmErrorCode createEscaper(Escaper newEscaper, const char* email, TechnionFaculty faculty, int typeSkill) {

	if( email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	if( faculty < 0 || faculty>17 || typeSkill < 0  || typeSkill > 10 ) return MTM_INVALID_PARAMETER;
	//TODO print by mtm_ex3
	//newUser = malloc(sizeof(struct escaper_t));
	//printf("address1: %p\n", (void*)newUser);
	if( newEscaper == NULL ) return MTM_OUT_OF_MEMORY;
	newEscaper->email = malloc(sizeof(char) * (strlen(email)+1));
	if( newEscaper->email == NULL ) {
		free(newEscaper);
		return MTM_OUT_OF_MEMORY;
	}
	strcpy( newEscaper->email, email);
	newEscaper->faculty = faculty;
	newEscaper->typeSkill = typeSkill;

	return MTM_SUCCESS;
}





/* Moved to system
MtmErrorCode addUser(Set setUser, const char* email, TechnionFaculty faculty, TypeSkill typeSkill) {
	if( setUser == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	if( faculty < 0 || faculty>17 || typeSkill < 0  || typeSkill > 10 ) return MTM_INVALID_PARAMETER;
	//TODO print by mtm_ex3
	User newUser = malloc(sizeof(struct user_t));
	if( newUser == NULL ) return MTM_OUT_OF_MEMORY;
	newUser->email = malloc(sizeof(char) * (strlen(email)+1));
	if( newUser->email == NULL ) {
		free(newUser);
		return MTM_OUT_OF_MEMORY;
	}
	strcpy(newUser->email, email);
	newUser->faculty = faculty;
	newUser->typeSkill = typeSkill;
	if( setIsIn( setUser, newUser ) ) {
		free(newUser->email);
		free(newUser);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	setAdd(setUser, newUser);
	free(newUser->email);
	free(newUser);
	return MTM_SUCCESS;
}*/

SetElement findEscaperByEmail( Set setEscaper, const char* email ) {
	if( setEscaper == NULL || email == NULL ) return NULL;
	SET_FOREACH(Escaper, val, setEscaper) {
		if ( strcmp(val->email, email) == 0) {
			return val;
		}
	}
	return NULL;
}


TechnionFaculty findEscaperFacultyFromEmail( Set setEscaper, const char* email ) {
	Escaper escaper = findEscaperByEmail( setEscaper, email );
	if ( escaper == NULL ) return UNKNOWN;
	if ( escaper->typeSkill == COMPANY ) return UNKNOWN;
	return escaper->faculty;
}


void printEscaper(SetElement escaper) {
	printf("\nPrint Escaper\n");
	printf("\n Escaper email: %s\n", ((Escaper)escaper)->email);
	printf("\n Escaper faculty: %d\n", ((Escaper)escaper)->faculty);
	printf("\n Escaper skill: %d\n", ((Escaper)escaper)->typeSkill);
}

