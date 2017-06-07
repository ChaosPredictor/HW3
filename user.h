/*
 * company.h
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#ifndef USER_H_
#define USER_H_

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

typedef struct user_t {
	char* email;
	TechnionFaculty faculty;
	int typeSkill;
} *User;



SetElement copyUser(SetElement user);

void freeUser(SetElement user);

int compareUsers(SetElement user1, SetElement user2);

MtmErrorCode createUser(User user, const char* email, TechnionFaculty faculty, int typeSkill);

//moved to system
//MtmErrorCode addUser(Set setUser, const char* email, TechnionFaculty faculty, TypeSkill typeSkill);

SetElement findUserFromEmail( Set setUser, const char* email );

bool emailValidity(const char* email);

//TODO remove
void printUser(SetElement user);

//moved to system
//MtmErrorCode removeCompany(Set setCompany, const char* email);

TechnionFaculty findCompanyFacultyFromEmail( Set setCompany, const char* email );

//moved to system
//MtmErrorCode removeEscaper(Set setCompany, const char* email);

TechnionFaculty findEscaperFacultyFromEmail( Set setUser, const char* email );



#endif /* USER_H_ */
