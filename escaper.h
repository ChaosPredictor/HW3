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
#include <stdlib.h>
#include "set.h"
#include "common.h"



typedef struct escaper_t {
	char* email;
	TechnionFaculty faculty;
	int typeSkill;
} *Escaper;




SetElement copyEscaper(SetElement escasper);

void freeEscaper(SetElement escasper);

int compareEscapers(const SetElement escasper1, const SetElement escasper2);

MtmErrorCode createEscaper(Escaper escaper, const char* email, \
		TechnionFaculty faculty, SkillLevel skill_level);

TechnionFaculty returnEscaperFaculty(const Escaper escaper );




#endif /* ESCAPER_H_ */
