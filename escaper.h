/*
 * escaper.h
 *
 *  Created on: May 30, 2017
 *      Author: master
 */

#ifndef ESCAPER_H_
#define ESCAPER_H_


#include <assert.h>
#include <string.h>

#include "order.h"
#include "mtm_escape.h"

//#include "visitor_room.h"
//TODO add related files

typedef struct escaper_t *Escaper;



MtmErrorCode addEscaper(Set setEscaper, const char* newEmail, TechnionFaculty faculty, int skill_level);

SetElement copyEscaper(SetElement escaper);

void freeEscaper(SetElement escaper);

int compareEscaperes(SetElement escaper1, SetElement escaper2);


#endif /* ESCAPER_H_ */
