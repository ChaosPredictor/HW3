/*
 * company.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#include "user.h"


//TODO all mails together



SetElement copyUser(SetElement user) {
	if ( user == NULL ) return NULL;
	assert(user);
	User newUser = malloc(sizeof(struct user_t));
	if ( newUser == NULL) return MTM_OUT_OF_MEMORY;

	newUser->email = malloc(sizeof(char) * (strlen(((User)user)->email) + 1));
	if ( newUser == NULL) {
		free( newUser );
		return MTM_OUT_OF_MEMORY;
	}

	strcpy(newUser->email, ((User)user)->email);
	newUser->typeSkill = ((User)user)->typeSkill;
	newUser->faculty = ((User)user)->faculty;

	return newUser;
}

void freeUser(SetElement user) {
	if ( user == NULL ) return;
	//Company tempCompany = (Company)company;
	//printf("email of Company4:%s\n", ((Company)company)->email);
	//char* temp = (((Company)company)->email);
	free(((User)user)->email);
	free((User)user);
}

int compareUsers(SetElement user1, SetElement user2) {
	return strcmp(((User)user1)->email, ((User)user2)->email);
}

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

SetElement findUserFromEmail( Set setUser, const char* email ) {
	if( setUser == NULL || email == NULL ) return NULL;
	SET_FOREACH(User, val, setUser) {
		if ( strcmp(val->email, email) == 0) {
			return val;
		}
	}
	return NULL;
}


bool emailValidity(const char* email) {
	size_t len = strlen(email);
	int count = 0;
	for (int i = 0; i < len; i++) {
		if( email[i] == '@' ) count++;
	}
	return ( count == 1);
}


MtmErrorCode removeCompany(Set setUser, const char* email) {
	if( setUser == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;

	User user = findUserFromEmail( setUser, email );
	if ( user == NULL || user->typeSkill != 0 ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

	//TODO not remove company with order
	//TODO remove all rooms of the company
	setRemove(setUser, user);
	return MTM_SUCCESS;

}

TechnionFaculty findCompanyFacultyFromEmail( Set setUser, const char* email ) {
	User user = findUserFromEmail( setUser, email );
	if ( user == NULL ) return UNKNOWN;
	if ( user->typeSkill != COMPANY ) return UNKNOWN;
	return user->faculty;
}


MtmErrorCode removeEscaper(Set setUser, const char* email) {
	if( setUser == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;

	User user = findUserFromEmail( setUser, email );
	if ( user == NULL || user->typeSkill == 0 ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;

	//TODO remove all his orders
	setRemove(setUser, user);
	return MTM_SUCCESS;

}

TechnionFaculty findEscaperFacultyFromEmail( Set setUser, const char* email ) {
	User user = findUserFromEmail( setUser, email );
	if ( user == NULL ) return UNKNOWN;
	if ( user->typeSkill == COMPANY ) return UNKNOWN;
	return user->faculty;
}




