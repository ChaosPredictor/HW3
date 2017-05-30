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



MtmErrorCode addCompany(Set setCompany, const char* email, TechnionFaculty faculty) {
	if( setCompany == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	//TODO print by mtm_ex3
	Company newCompany = malloc(sizeof(struct company_t));
	if( newCompany == NULL ) return MTM_OUT_OF_MEMORY;
	newCompany->email = malloc(sizeof(char) * (strlen(email)+1));
	if( newCompany->email == NULL ) {
		free(newCompany);
		return MTM_OUT_OF_MEMORY;
	}
	strcpy(newCompany->email, email);
	newCompany->faculty = faculty;
	if( setIsIn( setCompany, newCompany ) ) {
		free(newCompany->email);
		free(newCompany);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	setAdd(setCompany, newCompany);
	free(newCompany->email);
	free(newCompany);
	return MTM_SUCCESS;
}

MtmErrorCode removeCompany(Set setCompany, char* email) {
	if( setCompany == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	//TODO not remove company with order
	//TODO remove all rooms of the company
	SET_FOREACH(Company, val, setCompany) {
		if ( strcmp(val->email, email) == 0) {
			//TODO if is order
			if ( false ) {
				return MTM_RESERVATION_EXISTS;
			} else {
				//TODO remove all rooms
				setRemove(setCompany, val);
				return MTM_SUCCESS;
			}
		}
	}
	return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

}


SetElement copyCompany(SetElement company){
	if ( company == NULL ) return NULL;
	assert(company);
	Company newCompany = malloc(sizeof(struct company_t));
	//TODO return from malloc
	//printf("size of Company1:%lu\n",sizeof(newCompany));

	newCompany->email = malloc(sizeof(char) * (strlen(((Company)company)->email) + 1));
	//TODO return from malloc
	//printf("size of Company2:%lu\n",sizeof(newCompany->email));

	strcpy(newCompany->email, ((Company)company)->email);
	//printf("email of Company2:%s\n", newCompany->email);

	//TODO return from malloc;
	newCompany->faculty = ((Company)company)->faculty;
	return newCompany != NULL ? newCompany : NULL;
}

void freeCompany(SetElement company){
	if ( company == NULL ) return;
	//Company tempCompany = (Company)company;
	//printf("email of Company4:%s\n", ((Company)company)->email);
	//char* temp = (((Company)company)->email);
	free(((Company)company)->email);
	free((Company)company);
}

int compareCompanies(SetElement company1, SetElement company2) {
	return strcmp(((Company)company1)->email, ((Company)company2)->email);
}


TechnionFaculty findFacultyFromEmail( Set setCompany, char* email ) {
	if( setCompany == NULL || email == NULL ) return UNKNOWN;
	SET_FOREACH(Company, val, setCompany) {
		if ( strcmp(val->email, email) == 0) {
			return val->faculty;
		}
	}
	return UNKNOWN;
}

bool emailValidity(const char* email) {
	size_t len = strlen(email);
	int count = 0;
	for (int i = 0; i < len; i++) {
		if( email[i] == '@' ) count++;
	}
	return ( count == 1);
}
