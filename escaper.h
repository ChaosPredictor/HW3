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



/* copy escaper function
 * @param
 *	escaper - a new escaper object that same to the original *
 * @return
 *	escaper - copy of the escaper if success
 *	NULL - otherwise (memory leak)
 */
SetElement copyEscaper(SetElement escasper);

/* free escpaer function
 * @param
 * 	escaper - an escaper to free
 */
void freeEscaper(SetElement escasper);

/* compare two escapers function
 * @param
 * 	escaper1 - first of the escapers to compare
 * 	escaper2 - second of the escapers to compare
 * @return
 * 	0 - escaper1 equal to escaper2 (email)
 * 	1 - escaper1 higher than escaper2 (email)
 * 	-1 - escaper2 higher than escaper1 (email)
 */
int compareEscapers(const SetElement escasper1, const SetElement escasper2);

/* create a new escaper function
 * @param
 * 	escaper - a new escaper object that will be initialized
 * 	email - email of the escaper
 * 	faculty - faculty of the escaper
 * 	skill_level - skill level of the escaper
 * @return
 *	MTM_OUT_OF_MEMORY - out of memory
 *	MTM_INVALID_PARAMETER - if one of the parameters invalid
 *	MTM_SUCCESS - company created
 */
MtmErrorCode createEscaper(Escaper escaper, const char* email, \
		TechnionFaculty faculty, SkillLevel skill_level);

TechnionFaculty returnEscaperFaculty(const Escaper escaper );




#endif /* ESCAPER_H_ */
