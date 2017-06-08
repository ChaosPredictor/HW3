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

	free(((Escaper)escaper)->email);
	free((Escaper)escaper);
}

int compareEscapers(const SetElement escaper1, const SetElement escaper2) {
	return strcmp(((Escaper)escaper1)->email, ((Escaper)escaper2)->email);
}


MtmErrorCode createEscaper(Escaper newEscaper, const char* email, TechnionFaculty faculty, int typeSkill) {

	if( email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	if( faculty < 0 || faculty>17 || typeSkill < 0  || typeSkill > 10 ) return MTM_INVALID_PARAMETER;

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

TechnionFaculty returnEscaperFaculty(const Escaper escaper ) {
	return escaper->faculty;
}

void printEscaper(SetElement escaper) {
	printf("\nPrint Escaper\n");
	printf("\n Escaper email: %s\n", ((Escaper)escaper)->email);
	printf("\n Escaper faculty: %d\n", ((Escaper)escaper)->faculty);
	printf("\n Escaper skill: %d\n", ((Escaper)escaper)->typeSkill);
}

