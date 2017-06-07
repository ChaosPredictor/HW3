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

//#include "visitor_room.h"
//TODO add related files

/* moved to system
typedef enum {
    COMPANY,
	ESCAPER_1,
	ESCAPER_2,
	ESCAPER_3,
	ESCAPER_4,
	ESCAPER_5,
	ESCAPER_6,
	ESCAPER_7,
	ESCAPER_8,
	ESCAPER_9,
	ESCAPER_10
} TypeSkill;
*/

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

//moved to system
//SetElement findEscaperByEmail( Set setEscaper, const char* email );


//TODO remove
void printEscaper(SetElement escaper);

// removed
//TechnionFaculty findEscaperFacultyFromEmail( Set setEscaper, const char* email );



#endif /* ESCAPER_H_ */
