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
	//Company tempCompany = (Company)company;
	//printf("email of Company4:%s\n", ((Company)company)->email);
	//char* temp = (((Company)company)->email);
	free(((Company)company)->email);
	free((Company)company);
}

int compareCompanies(SetElement company1, SetElement company2) {
	return strcmp(((Company)company1)->email, ((Company)company2)->email);
}




MtmErrorCode createCompany(Company company, const char* email, TechnionFaculty faculty) {

	if( email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	if( faculty < 0 || faculty>17 ) return MTM_INVALID_PARAMETER;
	//TODO print by mtm_ex3
	//newUser = malloc(sizeof(struct user_t));
	//printf("address1: %p\n", (void*)newUser);
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





/* Moved to system
MtmErrorCode addUser(Set setUser, const char* email, TechnionFaculty faculty, TypeSkill typeSkill) {
	if( setUser == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	if( faculty < 0 || faculty>17 || typeSkill < 0  || typeSkill > 10 ) return MTM_INVALID_PARAMETER;
	//TODO print by mtm_ex3
	User newUser = malloc(sizeof(struct user_t));
	if( newUser == NULL ) return MTM_OUT_OF_MEMORY;
	newUser->email = malloc(sizeof(char) * (strlen(email)+1));
	if( newUser->email == NULL ) {
		free(newUser);
		return MTM_OUT_OF_MEMORY;
	}
	strcpy(newUser->email, email);
	newUser->faculty = faculty;
	newUser->typeSkill = typeSkill;
	if( setIsIn( setUser, newUser ) ) {
		free(newUser->email);
		free(newUser);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	setAdd(setUser, newUser);
	free(newUser->email);
	free(newUser);
	return MTM_SUCCESS;
}

SetElement findCompanyByEmail( Set setCompany, const char* email ) {
	if( setCompany == NULL || email == NULL ) return NULL;
	SET_FOREACH(Company, val, setCompany) {
		if ( strcmp(val->email, email) == 0) {
			return val;
		}
	}
	return NULL;
}
*/



/* moved to system
MtmErrorCode removeCompany(Set setUser, const char* email) {
	if( setUser == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;

	User user = findUserFromEmail( setUser, email );
	if ( user == NULL || user->typeSkill != 0 ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

	//TODO not remove company with order
	//TODO remove all rooms of the company
	setRemove(setUser, user);
	return MTM_SUCCESS;
}*/

TechnionFaculty findCompanyFacultyFromEmail( Set setCompany, const char* email ) {
	Company company = findCompanyByEmail( setCompany, email );
	if ( company == NULL ) return UNKNOWN;
	return company->faculty;
}

/* moved to system
MtmErrorCode removeEscaper(Set setUser, const char* email) {
	if( setUser == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;

	User user = findUserFromEmail( setUser, email );
	if ( user == NULL || user->typeSkill == 0 ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;

	//TODO remove all his orders
	setRemove(setUser, user);
	return MTM_SUCCESS;
}*/




void printCompany(SetElement company) {
	printf("\nPrint Company\n");
	printf("\n Company email: %s\n", ((Company)company)->email);
	printf("\n Company faculty: %d\n", ((Company)company)->faculty);
}
