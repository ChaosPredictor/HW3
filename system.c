/*
 * mtm_escape.c
 *
 *  Created on: May 27, 2017
 *      Author: master
 */

#include "system.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENG 200
#define MAX_COMMAND_LENG 7




//static SetElement copyCompany(SetElement company);
//static void freeCompany(SetElement company);
//static int compareCompanies(SetElement company1, SetElement company2);

int main(int argc, char *argv[]) {

	FILE *file = NULL;
	//FILE *file = fopen("./tests/EscapeTechnion/test1.in", "r");

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

	char line[MAX_NAME_LENG];

	Set users = setCreate(copyUser, freeUser, compareUsers);

	while ( fgets(line, MAX_NAME_LENG, file) != NULL) {

		const char* firstNonSpace = line;
		while(*firstNonSpace != '\0' && isspace(*firstNonSpace)) {
			++firstNonSpace;
		}
		size_t len = strlen(firstNonSpace)+1;
		memmove(line, firstNonSpace, len);
		//const char *firstChar[1] = &a[0];
		if ( strcmp(line,"") != 0 && line[0] != '#' ) {
			char *temp = malloc(sizeof(char) * (strlen(line) + 1));
			strcpy(temp,line);
			char* command = NULL;//= malloc(sizeof(char) * ( MAX_COMMAND_LENG + 1));
			command = strtok(temp, " ");
			if ( strcmp(command,"company") == 0) {
				char* subCommand = NULL;
				subCommand = strtok(NULL, " ");
				if ( strcmp(subCommand,"add") == 0 ) {
					char* email = strtok(NULL, " ");
					int faculty = atoi( strtok(NULL, " ") );
					addUser(users, email, faculty, COMPANY);
				} else if ( strcmp(subCommand,"remove") == 0 ) {
					printf("this is remove company\n");
					printf("your input a: %s", line);

				}
			} else if ( strcmp(command,"room") == 0) {
				printf("this is room\n");
				printf("your input a: %s", line);


			} else {
				printf("this is not company\n");
				printf("your input a: %s", line);

			}
			//free( command );
			free( temp );
			//free( command );


			//int hour = atoi( strtok(NULL, "-") );
		}
	}
	//EscapeSystem *sys=NULL;
	//Result r=OK;

	//r=create_system("test_1.txt", &sys);

	//createSystem(&sys);

	//createCompanySet(sys);

	//addCompany(sys->companies, "sdfefdgdfh5654654fgjhfgsdf", CIVIL_ENGINEERING);

	//int size = listGetSize(sys->users);
	//printf("size: %d\n", size);

	//addCompany(Set setCompany, char* newEmail, TechnionFaculty faculty)

	//destroySystem(sys);
	setDestroy(users);

	fclose(file);
	return 0;
}

MtmErrorCode createSystem(EscapeSystem **sys) {
	*sys = malloc(sizeof(**sys));

	//sys->days = createDays();
	return MTM_SUCCESS;
}

MtmErrorCode destroySystem(EscapeSystem *sys) {
	//setClear(sys->users);
	//setDestroy(sys->users);
	//setDestroy(sys->rooms);
	//setDestroy(sys->days);
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
	//sys->companies = setCreate(copyUser, freeUser, compareUsers);
	//int size = setGetSize(sys->company);
	//printf("size: %d\n", size);
	//*sys->company = setCreate(copyCompany, freeCompany, compareCompanies);
	//TODO check not NULL
	return MTM_SUCCESS;
}


MtmErrorCode printanOrder(FILE* outputChannel, EscapeSystem system, Order order) {


	return MTM_SUCCESS;


	//mtmPrintOrder(outputChannel, char* email, int skill, TechnionFaculty client_faculty, char* company_email, TechnionFaculty room_faculty, int id, int hour, int difficulty, int num_ppl, int totalPrice);
}



MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem system) {
	List days = system->days;
	Day today = listGetFirst(days);
	List orders = today->dayOrders;
	mtmPrintDayHeader(stdout, today->dayNumber, listGetSize(orders));

	Order order = listGetFirst(orders);
	while ( order != NULL ) {

	}

	if ( listGetSize(days) == 1 ) {
		listInsertLast(days, createDay(today->dayNumber+1));
	}
	listRemoveCurrent(days);
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

