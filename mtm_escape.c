/*
 * mtm_escape.c
 *
 *  Created on: May 27, 2017
 *      Author: master
 */

#include "mtm_escape.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENG 200


struct EscapeSystem_t
{
	int temp;
	Set companies;
	Set rooms;
};


//static SetElement copyCompany(SetElement company);
//static void freeCompany(SetElement company);
//static int compareCompanies(SetElement company1, SetElement company2);

int main(int argc, char *argv[]) {

	FILE *file = stdin;

	if ( !(argc == 1 || argc == 3 || argc == 5) ) {
		printf("‫‪MTM_INVALID_COMMAND_LINE_PARAMETERS.‬‬\n");
		//TODO change it to mtm_ex3 print function
		fclose(file);
		return -1;
	} else if ( argc == 5 ) {
		if ( strcmp(argv[1],"-i") == 0 ) {
			file = fopen(argv[2], "r");
		} else if ( strcmp(argv[3],"-i") == 0 ) {
			file = fopen(argv[4], "r");
		}
		if ( file == NULL ) {
			printf("MTM_CANNOT_OPEN_FILE.");
			//TODO change it to mtm_ex3 print function
			fclose(file);
			return -1;
		}

		//TODO output
	}

	char a[MAX_NAME_LENG];

	while ( fgets(a, MAX_NAME_LENG, file) != NULL) {

		const char* firstNonSpace = a;
		while(*firstNonSpace != '\0' && isspace(*firstNonSpace)) {
			++firstNonSpace;
		}
		size_t len = strlen(firstNonSpace)+1;
		memmove(a, firstNonSpace, len);
		//const char *firstChar[1] = &a[0];
		if ( strcmp(a,"") != 0 && a[0] != '#' ) {
			printf("your input a: %s", a);
		}

	}
	EscapeSystem *sys=NULL;
	//Result r=OK;

	//r=create_system("test_1.txt", &sys);

	createSystem(&sys);

	createCompanySet(sys);

	addCompany(sys->companies, "sdfefdgdfh5654654fgjhfgsdf", CIVIL_ENGINEERING);

	int size = setGetSize(sys->companies);
	printf("size: %d\n", size);

	//addCompany(Set setCompany, char* newEmail, TechnionFaculty faculty)

	destroySystem(sys);

	fclose(file);
}

MtmErrorCode createSystem(EscapeSystem **sys) {
	*sys = malloc(sizeof(**sys));
	return MTM_SUCCESS;
}

MtmErrorCode destroySystem(EscapeSystem *sys) {
	setClear(sys->companies);
	setDestroy(sys->companies);
	free(sys);
	return MTM_SUCCESS;
}

MtmErrorCode createCompanySet(EscapeSystem *sys) {
	//Set set = setCreate(copyCompany, freeCompany, compareCompanies);
	//int size = setGetSize(set);
	//printf("size: %d", size);
	//Set company = setCreate(copyCompany, freeCompany, compareCompanies);
	//int size = setGetSize(company);
	//printf("size: %d", size);
	//sys->company = malloc(sizeof(*Set));
	//sys->company = malloc(sizeof(Set*));
	sys->companies = setCreate(copyCompany, freeCompany, compareCompanies);
	//int size = setGetSize(sys->company);
	//printf("size: %d\n", size);
	//*sys->company = setCreate(copyCompany, freeCompany, compareCompanies);
	//TODO check not NULL
	return MTM_SUCCESS;
}


/*
static SetElement copyCompany(SetElement company){
	assert(company);
	Company newCompany = malloc(sizeof(newCompany));
	//TODO return from malloc;

	newCompany->email = malloc(strlen(((Company)company)->email)+1);
	strcpy(newCompany->email, ((Company)company)->email);
	//TODO return from malloc;
	newCompany->faculty = ((Company)company)->faculty;
	return newCompany != NULL ? newCompany : NULL;
}

static void freeCompany(SetElement company){
	free(((Company)company)->email);
	free(company);
}

static int compareCompanies(SetElement company1, SetElement company2) {
	return strcmp(company1, company2);
}*/

