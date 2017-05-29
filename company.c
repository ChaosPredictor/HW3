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



MtmErrorCode addCompany(Set setCompany, char* email, TechnionFaculty faculty2) {
	//TODO check email exist
	//TODO check email not in the list
	Company newCompany = malloc(sizeof(struct company_t));
	newCompany->email = malloc(sizeof(char) * (strlen(email)+1));
	strcpy(newCompany->email, email);
	newCompany->faculty = faculty2;
	setAdd(setCompany, newCompany);
	free(newCompany->email);
	free(newCompany);
	return MTM_SUCCESS;
}


SetElement copyCompany(SetElement company){
	if ( company == NULL ) return NULL;
	assert(company);
	Company newCompany = malloc(sizeof(struct company_t));
	//TODO return from malloc
	//printf("size of Company1:%lu\n",sizeof(newCompany));

	newCompany->email = malloc(sizeof(char) * (strlen(((Company)company)->email) + 1));
	//printf("size of Company2:%lu\n",sizeof(newCompany->email));

	strcpy(newCompany->email, ((Company)company)->email);
	//printf("email of Company2:%s\n", newCompany->email);

	//TODO return from malloc;
	newCompany->faculty = ((Company)company)->faculty;
	return newCompany != NULL ? newCompany : NULL;
}

void freeCompany(SetElement company){
	//Company tempCompany = (Company)company;
	printf("email of Company4:%s\n", ((Company)company)->email);
	//char* temp = (((Company)company)->email);
	free(((Company)company)->email);
	free((Company)company);
}

int compareCompanies(SetElement company1, SetElement company2) {
	return strcmp(company1, company2);
}
