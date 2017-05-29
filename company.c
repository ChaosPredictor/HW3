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



MtmErrorCode addCompany(Set setCompany, char* email, TechnionFaculty faculty) {
	//TODO check email exist
	//TODO check email not in the list
	Company newCompany = malloc(sizeof(struct company_t));
	newCompany->email = malloc(strlen(email)+1);
	strcpy(newCompany->email, email);
	newCompany->faculty = faculty;
	setAdd(setCompany, newCompany);

	return MTM_SUCCESS;
}


SetElement copyCompany(SetElement company){
	assert(company);
	Company newCompany = malloc(sizeof(struct company_t));
	//TODO return from malloc;
	newCompany->email = malloc(strlen(((Company)company)->email)+1);
	strcpy(newCompany->email, ((Company)company)->email);
	//TODO return from malloc;
	newCompany->faculty = ((Company)company)->faculty;
	return newCompany != NULL ? newCompany : NULL;
}

void freeCompany(SetElement company){
	//free((*company)->email);
	free(company);
}

int compareCompanies(SetElement company1, SetElement company2) {
	return strcmp(company1, company2);
}
