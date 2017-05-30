/*
 * company.h
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#ifndef COMPANY_H_
#define COMPANY_H_

#include <assert.h>
#include <string.h>


#include "order.h"
#include "mtm_escape.h"

//#include "visitor_room.h"
//TODO add related files

typedef struct company_t *Company;



MtmErrorCode addCompany(Set setCompany, const char* newEmail, TechnionFaculty faculty);

MtmErrorCode removeCompany(Set setCompany, char* email);

bool emailValidity(const char* email);

SetElement copyCompany(SetElement company);

void freeCompany(SetElement company);

int compareCompanies(SetElement company1, SetElement company2);



#endif /* COMPANY_H_ */
