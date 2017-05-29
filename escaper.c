/*
 * escaper.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */


#include "escaper.h"

struct escaper_t {
	char* email;
	TechnionFaculty faculty;
	int skill_level;
};



//TODO all mails together



MtmErrorCode addEscaper(Set setEscaper, const char* email, TechnionFaculty faculty, int skill_level) {
	//TODO check email exist
	//TODO check email not in the list
	Escaper newEscaper = malloc(sizeof(struct escaper_t));
	newEscaper->email = malloc(sizeof(char) * (strlen(email)+1));
	strcpy(newEscaper->email, email);
	newEscaper->faculty = faculty;
	newEscaper->skill_level = skill_level;
	setAdd(setEscaper, newEscaper);
	free(newEscaper->email);
	free(newEscaper);
	return MTM_SUCCESS;
}

SetElement copyEscaper(SetElement escaper){
	if ( escaper == NULL ) return NULL;
	assert(escaper);
	Escaper newEscaper = malloc(sizeof(struct escaper_t));
	//TODO return from malloc
	//printf("size of Escaper1:%lu\n",sizeof(newEscaper));

	newEscaper->email = malloc(sizeof(char) * (strlen(((Escaper)escaper)->email) + 1));
	//TODO return from malloc
	//printf("size of Escaper2:%lu\n",sizeof(newEscaper->email));

	strcpy(newEscaper->email, ((Escaper)escaper)->email);
	//printf("email of Escaper2:%s\n", newEscaper->email);

	//TODO return from malloc;
	newEscaper->faculty = ((Escaper)escaper)->faculty;
	return newEscaper != NULL ? newEscaper : NULL;
}

void freeEscaper(SetElement escaper){
	if ( escaper == NULL ) return;
	//Escaper tempEscaper = (Escaper)escaper;
	//printf("email of Escaper4:%s\n", ((Escaper)escaper)->email);
	//char* temp = (((Escaper)escaper)->email);
	free(((Escaper)escaper)->email);
	free((Escaper)escaper);
}

int compareEscapers(SetElement escaper1, SetElement escaper2) {
	return strcmp(((Escaper)escaper1)->email, ((Escaper)escaper2)->email);
}

