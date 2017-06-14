/*
 * company.h
 *
 *  Created on: Jun 7, 2017
 *      Author: master
 */

#ifndef COMPANY_H_
#define COMPANY_H_

#include <assert.h>
#include "set.h"
#include "common.h"



typedef struct company_t {
	char* email;
	TechnionFaculty faculty;
} *Company;


/* copy company function
 * @param
 * 	company - a new company object that same to the original
 * @return
 *	copmany - copy of the company if success
 *	NULL - otherwise (memory leak)
 */
SetElement copyCompany(SetElement company);

/* free company function
 * @param
 * 	company - a company to free
 */
void freeCompany(SetElement company);

/* compare two companies function
 * @param
 * 	company1 - first of the companies to compare
 * 	company2 - second of the companies to compare
 * @return
 * 	0 - company1 equal to company2 (email)
 * 	1 - company1 higher than company2 (email)
 * 	-1 - company2 higher than company1 (email)
 */
int compareCompanies(const SetElement company1, const SetElement company2);

/* create a new company function
 * @param
 * 	company - a new company object that will be initialized
 * 	email - email of the company
 * 	faculty - faculty of the company
 * @return
 *	MTM_OUT_OF_MEMORY - out of memory
 *	MTM_INVALID_PARAMETER - if one of the parameters invalid
 *	MTM_SUCCESS - company created
 */
MtmErrorCode createCompany(Company company, const char* email, \
		TechnionFaculty faculty);

TechnionFaculty returnCompanyFaculty(const Company company );

#endif /* COMPANY_H_ */
