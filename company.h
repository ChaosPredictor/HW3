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
	int numberOfRooms;
} *Company;



SetElement copyCompany(SetElement company);

void freeCompany(SetElement company);

int compareCompanies(const SetElement company1, const SetElement company2);

MtmErrorCode createCompany(Company company, const char* email, TechnionFaculty faculty);

TechnionFaculty returnCompanyFaculty(const Company company );

MtmErrorCode addARoomToCompany(Company company);

MtmErrorCode removeARoomFromCompany(Company company);


#endif /* COMPANY_H_ */
