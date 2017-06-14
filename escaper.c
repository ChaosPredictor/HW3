/*
 * company.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#include "escaper.h"




SetElement copyEscaper(SetElement escaper) {
	if ( escaper == NULL ) return NULL;
	assert(escaper);
	Escaper new_escaper = malloc(sizeof(struct escaper_t));
	if ( new_escaper == NULL) return MTM_OUT_OF_MEMORY;

	new_escaper->email = malloc(sizeof(char) * \
			(strlen(((Escaper)escaper)->email) + 1));
	if ( new_escaper == NULL) {
		free( new_escaper );
		return MTM_OUT_OF_MEMORY;
	}

	strcpy(new_escaper->email, ((Escaper)escaper)->email);
	new_escaper->typeSkill = ((Escaper)escaper)->typeSkill;
	new_escaper->faculty = ((Escaper)escaper)->faculty;

	return new_escaper;
}

void freeEscaper(SetElement escaper) {
	if ( escaper == NULL ) return;

	free(((Escaper)escaper)->email);
	free((Escaper)escaper);
}

int compareEscapers(const SetElement escaper1, const SetElement escaper2) {
	return strcmp(((Escaper)escaper1)->email, ((Escaper)escaper2)->email);
}


MtmErrorCode initEscaper(Escaper new_escaper, const char* email, \
		TechnionFaculty faculty, SkillLevel skill_level) {
	if( email == NULL ) return MTM_INVALID_PARAMETER;
	new_escaper->email = malloc(sizeof(char) * (strlen(email)+1));
	if( new_escaper->email == NULL ) return MTM_OUT_OF_MEMORY;
	if( !emailValidation(email) || !facultyValidation(faculty) || \
			!skillLevelValidation(skill_level)) {
		free( new_escaper->email );
		return MTM_INVALID_PARAMETER;
	}
	strcpy( new_escaper->email, email);
	new_escaper->faculty = faculty;
	new_escaper->typeSkill = skill_level;
	return MTM_SUCCESS;
}

TechnionFaculty returnEscaperFaculty(const Escaper escaper ) {
	if ( escaper == NULL ) return UNKNOWN;
	return escaper->faculty;
}

