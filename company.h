/*
 * company.h
 *
 *  Created on: Jun 7, 2017
 *      Author: master
 */

#ifndef COMPANY_H_
#define COMPANY_H_

#include <assert.h>
#include <string.h>
#include "set.h"
#include "order.h"
#include "system.h"

//#include "visitor_room.h"
//TODO add related files



typedef struct company_t {
	char* email;
	TechnionFaculty faculty;
} *Company;



SetElement copyCompany(SetElement company);

void freeCompany(SetElement company);

int compareCompanies(SetElement company1, SetElement company2);

MtmErrorCode createCompany(Company company, const char* email, TechnionFaculty faculty);

//TODO move to system
SetElement findCompanyByEmail( Set setCompany, const char* email );

TechnionFaculty findCompanyFacultyFromEmail( Set setCompany, const char* email );



#endif /* COMPANY_H_ */
