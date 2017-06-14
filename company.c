/*
 * company.c
 *
 *  Created on: Jun 7, 2017
 *      Author: master
 */


#include "company.h"




SetElement copyCompany(SetElement company) {
	if ( company == NULL ) return NULL;
	assert(company);
	Company new_company = malloc(sizeof(struct company_t));
	if ( new_company == NULL) return NULL;

	new_company->email = malloc(sizeof(char) * \
			(strlen(((Company)company)->email) + 1));
	if ( new_company == NULL) {
		free( new_company );
		return NULL;
	}

	strcpy(new_company->email, ((Company)company)->email);
	new_company->faculty = ((Company)company)->faculty;
	return new_company;
}

void freeCompany(SetElement company) {
	if ( company == NULL ) return;
	free(((Company)company)->email);
	free((Company)company);
}

int compareCompanies(const SetElement company1, const SetElement company2) {
	return strcmp(((Company)company1)->email, ((Company)company2)->email);
}

MtmErrorCode initCompany(Company company, const char* email, \
		TechnionFaculty faculty) {

	if( email == NULL || company == NULL ) return MTM_INVALID_PARAMETER;
	company->email = malloc(sizeof(char) * (strlen(email)+1));
	if( company->email == NULL ) {
		free(company);
		return MTM_OUT_OF_MEMORY;
	}
	if( !emailValidation(email) || !facultyValidation(faculty)) \
			return MTM_INVALID_PARAMETER;

	strcpy( company->email, email);
	company->faculty = faculty;

	return MTM_SUCCESS;
}

TechnionFaculty returnCompanyFaculty(const Company company ) {
	if ( company == NULL ) return UNKNOWN;
	return company->faculty;
}
