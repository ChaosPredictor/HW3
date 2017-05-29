/*
 * company.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#include "company.h"

struct company_t {
	char* email;
	TechnionFaculty faculty;
};

//TODO all mails together



MtmErrorCode addCompany(Set *company, char* email, char* faculty) {
	return MTM_SUCCESS;
}


SetElement copyCompany(SetElement company){
	assert(company);
	Company newCompany = malloc(sizeof(newCompany));
	//TODO return from malloc;

	newCompany->email = malloc(strlen(((Company)company)->email)+1);
	strcpy(newCompany->email, ((Company)company)->email);
	//TODO return from malloc;
	newCompany->faculty = ((Company)company)->faculty;
	return newCompany != NULL ? newCompany : NULL;
}

void freeCompany(SetElement company){
	free(((Company)company)->email);
	free(company);
}

int compareCompanies(SetElement company1, SetElement company2) {
	return strcmp(company1, company2);
}
