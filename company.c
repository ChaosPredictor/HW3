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
	Company newCompany = malloc(sizeof(struct company_t));
	if ( newCompany == NULL) return MTM_OUT_OF_MEMORY;

	newCompany->email = malloc(sizeof(char) * (strlen(((Company)company)->email) + 1));
	if ( newCompany == NULL) {
		free( newCompany );
		return MTM_OUT_OF_MEMORY;
	}

	strcpy(newCompany->email, ((Company)company)->email);
	newCompany->faculty = ((Company)company)->faculty;
	return newCompany;
}

void freeCompany(SetElement company) {
	if ( company == NULL ) return;
	free(((Company)company)->email);
	free((Company)company);
}

int compareCompanies(const SetElement company1, const SetElement company2) {
	return strcmp(((Company)company1)->email, ((Company)company2)->email);
}

MtmErrorCode createCompany(Company company, const char* email, TechnionFaculty faculty) {

	if( email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidation(email) ) return MTM_INVALID_PARAMETER;
	if( faculty < 0 || faculty > 17 ) return MTM_INVALID_PARAMETER;

	if( company == NULL ) return MTM_OUT_OF_MEMORY;
	company->email = malloc(sizeof(char) * (strlen(email)+1));
	if( company->email == NULL ) {
		free(company);
		return MTM_OUT_OF_MEMORY;
	}
	strcpy( company->email, email);
	company->faculty = faculty;

	return MTM_SUCCESS;
}

TechnionFaculty returnCompanyFaculty(const Company company ) {
	if ( company == NULL ) return UNKNOWN;
	return company->faculty;
}
