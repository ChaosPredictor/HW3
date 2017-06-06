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
#define NUMBER_OF_BEST 3

const int NUMBER_OF_FACULTIES = UNKNOWN;





//static SetElement copyCompany(SetElement company);
//static void freeCompany(SetElement company);
//static int compareCompanies(SetElement company1, SetElement company2);

int main(int argc, char *argv[]) {

	FILE *filein = NULL;
	FILE *fileout = NULL;
	//FILE *file = fopen("./tests/EscapeTechnion/test1.in", "r");

	if ( !(argc == 1 || argc == 3 || argc == 5) ) {
		printf("‫‪MTM_INVALID_COMMAND_LINE_PARAMETERS.‬‬\n");
		//TODO change it to mtm_ex3 print function
		//fclose(filein);
		return -1;
	} else if ( argc == 5 ) {
		if ( strcmp(argv[1],"-i") == 0 ) {
			//TODO check if opened
			filein = fopen(argv[2], "r");
			fileout = fopen(argv[4], "w");
		} else if ( strcmp(argv[3],"-i") == 0 ) {
			//TODO check if opened
			filein = fopen(argv[4], "r");
			fileout = fopen(argv[2], "w");
		}
		if ( filein == NULL ) {
			printf("MTM_CANNOT_OPEN_FILE.");
			//TODO change it to mtm_ex3 print function
			//fclose(fileout);
			return -1;
		}

		//TODO output
	} //TODO 3 argc case

	char line[MAX_NAME_LENG];

	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	system->users = setCreate(copyUser, freeUser, compareUsers);
	//system->users = &use;
	system->rooms = setCreate(copyRoom, freeRoom, compareRooms);
	//system->days = createDays();
	system->days = createDays();

	system->faculties = createFaculties(NUMBER_OF_FACULTIES);
	//printf("address %p", (void*)days);

	while ( fgets(line, MAX_NAME_LENG, filein) != NULL) {

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
			if ( strcmp(command,"company" ) == 0) {
				char* subCommand = NULL;
				subCommand = strtok(NULL, " ");
				if ( strcmp(subCommand,"add" ) == 0 ) {
					char* email = strtok(NULL, " ");
					int faculty = atoi( strtok(NULL, " ") );
					addUser(system->users, email, faculty, COMPANY);
				} else if ( strcmp(subCommand,"remove") == 0 ) {
					printf("this is remove company\n");
					printf("your input a: %s", line);

				}
			} else if ( strcmp(command,"room" ) == 0) {
				char* subCommand = NULL;
				subCommand = strtok(NULL, " ");
				if ( strcmp(subCommand, "add" ) == 0 ) {
					//printf("this is add room\n");
					//printf("your input a: %s", line);
					char* email = strtok(NULL, " ");
					int id = atoi( strtok(NULL, " ") );
					int price = atoi( strtok(NULL, " ") );
					int num_ppl = atoi( strtok(NULL, " ") );
					char* working_hrs = strtok(NULL, " ");
					int difficulty = atoi( strtok(NULL, " ") );
					addRoom(system->rooms, system->users, email, id, price, num_ppl, working_hrs, difficulty);
				} else {
					printf("this is remove room\n");
					printf("your input a: %s", line);
				}

			} else if ( strcmp(command,"escaper") == 0) {
				//printf("this is escaper\n");
				//printf("your input a: %s", line);
				char* subCommand = NULL;
				subCommand = strtok(NULL, " ");
				if ( strcmp(subCommand, "add" ) == 0 ) {
					//printf("this is add escaper\n");
					//printf("your input a: %s", line);
					char* email = strtok(NULL, " ");
					int faculty = atoi( strtok(NULL, " ") );
					int skill_level = atoi( strtok(NULL, " ") );
					addUser(system->users, email, faculty, skill_level);
				} else if ( strcmp(subCommand, "order" ) == 0 ) {
					//printf("this is escaper order\n");
					//printf("your input a: %s", line);
					char* email = strtok(NULL, " ");
					int faculty = atoi( strtok(NULL, " ") );
					int id = atoi( strtok(NULL, " ") );
					char* time = strtok(NULL, " ");
					int num_ppl = atoi( strtok(NULL, " ") );
					addOrder(system->days, system->users, system->rooms, email, faculty, id, time, num_ppl);
				}  else if ( strcmp(subCommand, "recommend" ) == 0 ) {
					//printf("this is escaper order\n");
					//printf("your input a: %s", line);
					char* email = strtok(NULL, " ");
					int num_ppl = atoi( strtok(NULL, " ") );
					addRecommendedOrder(system->days, system->users, system->rooms, email, num_ppl );
				} else {
					printf("this is remove escaper\n");
					printf("your input a: %s", line);
				}

			} else if ( strcmp(command,"report") == 0) {
				//printf("this is escaper\n");
				//printf("your input a: %s", line);
				char* subCommand = NULL;
				subCommand = strtok(NULL, " ");
				if ( strcmp(subCommand, "day\n" ) == 0 ) {
					//printf("this is add escaper\n");
					//printf("your input a: %s", line);
					reportDay(fileout, system);
				} else if ( strcmp(subCommand, "best\n" ) == 0 ) {
					//printf("this is add escaper\n");
					//printf("your input a: %s", line);
					reportBest(fileout, system);
				} else  {
					printf("this is report not day\n");
					printf("your input a: %s", line);
				}

			} else {
				printf("this is not\n");
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
	listDestroy(system->days);
	listDestroy(system->faculties);
	setDestroy(system->rooms);
	setDestroy(system->users);

	free(system);

	fclose(fileout);
	fclose(filein);
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
	//List days = system->days;
	Day today = listGetFirst(system->days);
	List orders = today->dayOrders;
	mtmPrintDayHeader(outputChannel, today->dayNumber, listGetSize(orders));


	User user = NULL;
	Room room = NULL;
	Order order = listGetFirst(orders);
	while ( order != NULL ) {
		//TODO check that escaper;
		user = findUserFromEmail( system->users, order->email );
		//printUser(user);
		room = findRoom(system->rooms, order->faculty, order->id);
		//printRoom(room);
		//printOrder(order);
		mtmPrintOrder(outputChannel, user->email, user->typeSkill, user->faculty, room->email, room->faculty, room->id, order->hour, room->difficulty, order->num_ppl, order->price);
		addIncomeToFaculty(system->faculties, room->faculty, order->price);
		order = listGetNext(orders);
	}
	mtmPrintDayFooter(outputChannel, today->dayNumber);

	if ( listGetSize(system->days) == 1 ) {
		Day day = createDay(today->dayNumber+1);
		listInsertLast(system->days, day);
		freeDay(day);
	}

	listRemoveCurrent(system->days);
	return MTM_SUCCESS;
}



MtmErrorCode reportBest(FILE* outputChannel, EscapeSystem system) {
	Day today = listGetFirst(system->days);

	mtmPrintFacultiesHeader(outputChannel, NUMBER_OF_FACULTIES, today->dayNumber, returnTotalRevenue(system->faculties));

	List bestList = returnBestNFaculties(system->faculties, NUMBER_OF_BEST);
	Faculty faculty = listGetFirst(bestList);
	while ( faculty != NULL ) {
		mtmPrintFaculty(outputChannel, faculty->id, faculty->income);
		faculty = listGetNext(bestList);
	}
	mtmPrintFacultiesFooter(outputChannel);


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

