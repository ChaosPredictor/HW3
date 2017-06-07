/*
 * company.h
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#ifndef ESCAPER_H_
#define ESCAPER_H_

#include <assert.h>
#include <string.h>
#include "set.h"
#include "order.h"
#include "system.h"



typedef struct escaper_t {
	char* email;
	TechnionFaculty faculty;
	int typeSkill;
} *Escaper;



SetElement copyEscaper(SetElement escasper);

void freeEscaper(SetElement escasper);

int compareEscapers(SetElement escasper1, SetElement escasper2);

MtmErrorCode createEscaper(Escaper escaper, const char* email, TechnionFaculty faculty, int typeSkill);

TechnionFaculty returnEscaperFaculty( Escaper escaper );


//TODO remove
void printEscaper(SetElement escaper);



#endif /* ESCAPER_H_ */
