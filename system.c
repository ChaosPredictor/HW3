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
	system->escapers = setCreate(copyEscaper, freeEscaper, compareEscapers);
	system->companies = setCreate(copyCompany, freeCompany, compareCompanies);
	system->rooms = setCreate(copyRoom, freeRoom, compareRooms);
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
					//TODO check return value
					addCompany(system, email, faculty );
				} else if ( strcmp(subCommand,"remove") == 0 ) {
					//printf("this is remove company\n");
					//printf("your input a: %s", line);
					char* email = strtok(NULL, " ");
					//TODO check return value
					removeCompany(system, email);
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
					//TODO check return value
					addRoom(system, email, id, price, num_ppl, working_hrs, difficulty);
				} if ( strcmp(subCommand, "remove\n" ) == 0 ) {
					//printf("this is add room\n");
					//printf("your input a: %s", line);
					int faculty = atoi( strtok(NULL, " ") );
					int id = atoi( strtok(NULL, " ") );
					//TODO check return value
					removeRoom(system, faculty, id);
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
					//TODO check return value
					addEscaper(system, email, faculty, skill_level);
				} else if ( strcmp(subCommand, "order" ) == 0 ) {
					//printf("this is escaper order\n");
					//printf("your input a: %s", line);
					char* email = strtok(NULL, " ");
					int faculty = atoi( strtok(NULL, " ") );
					int id = atoi( strtok(NULL, " ") );
					char* time = strtok(NULL, " ");
					int num_ppl = atoi( strtok(NULL, " ") );
					//TODO check return value
					addOrder(system, email, faculty, id, time, num_ppl);
				}  else if ( strcmp(subCommand, "recommend" ) == 0 ) {
					//printf("this is escaper order\n");
					//printf("your input a: %s", line);
					char* email = strtok(NULL, " ");
					int num_ppl = atoi( strtok(NULL, " ") );
					//TODO check return value
					addRecommendedOrder(system, email, num_ppl );
				} else if ( strcmp(subCommand, "remove" ) == 0 ) {
					//printf("this is escaper order\n");
					//printf("your input a: %s", line);
					char* email = strtok(NULL, " ");
					//TODO check return value
					removeEscaper(system, email);
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
					//TODO check return value
					reportDay(fileout, system);
				} else if ( strcmp(subCommand, "best\n" ) == 0 ) {
					//printf("this is add escaper\n");
					//printf("your input a: %s", line);
					//TODO check return value
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
	setDestroy(system->escapers);
	setDestroy(system->companies);

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

//To break to addCompany and addEscaper
MtmErrorCode addCompany(EscapeSystem sys, const char* email, TechnionFaculty faculty) {
	Company newCompany = malloc(sizeof(struct company_t));
	//TODO check return value
	createCompany(newCompany, email, faculty);

	//TODO check both escaper and company
	if( setIsIn( sys->companies, newCompany ) ) {
		free(newCompany->email);
		free(newCompany);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	setAdd(sys->companies, newCompany);
	free(newCompany->email);
	free(newCompany);
	return MTM_SUCCESS;
}

MtmErrorCode removeCompany(EscapeSystem sys, const char* email) {
	if( sys->companies == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;

	Company company = findCompanyByEmail( sys->companies , email );
	if ( company == NULL ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

	//TODO not remove company with order
	//TODO remove all rooms of the company
	setRemove(sys->companies , company);
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



MtmErrorCode addEscaper(EscapeSystem sys, const char* email, TechnionFaculty faculty, TypeSkill typeSkill) {
	Escaper newEscaper = malloc(sizeof(struct escaper_t));
	//TODO check return value
	createEscaper(newEscaper, email, faculty, typeSkill);

	//TODO check both escaper and company
	if( setIsIn( sys->escapers, newEscaper ) ) {
		free(newEscaper->email);
		free(newEscaper);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	setAdd(sys->escapers, newEscaper);
	free(newEscaper->email);
	free(newEscaper);
	return MTM_SUCCESS;
}

MtmErrorCode removeEscaper(EscapeSystem sys, const char* email) {
	if( sys->escapers == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;

	Escaper escaper = findEscaperByEmail( sys->escapers, email );
	if ( escaper == NULL || escaper->typeSkill == 0 ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;

	//TODO remove all his orders
	setRemove(sys->escapers, escaper);
	return MTM_SUCCESS;
}

SetElement findEscaperByEmail( Set setEscaper, const char* email ) {
	if( setEscaper == NULL || email == NULL ) return NULL;
	SET_FOREACH(Escaper, val, setEscaper) {
		if ( strcmp(val->email, email) == 0) {
			return val;
		}
	}
	return NULL;
}



MtmErrorCode addRoom(EscapeSystem sys, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty) {
	if ( sys == NULL ) return MTM_INVALID_PARAMETER;
	if ( email == NULL || !emailValidity(email) )  return MTM_INVALID_PARAMETER;

	TechnionFaculty faculty = findCompanyFacultyFromEmail(sys->companies, email);
	if ( faculty == UNKNOWN ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

	//TODO check email exist
	//TODO check email not in the list
	//TODO faculty & id unic
	Room newRoom = malloc(sizeof(struct room_t));
	if ( newRoom == NULL) {
		return MTM_OUT_OF_MEMORY;
	}

	createRoom(newRoom, email, id, faculty, price, num_ppl, working_hrs, difficulty);

	if( setIsIn(sys->rooms, newRoom) ) {
		free(newRoom->email);
		free(newRoom);
		return MTM_ID_ALREADY_EXIST;
	}

	setAdd(sys->rooms, newRoom);
	free(newRoom->email);
	free(newRoom);
	return MTM_SUCCESS;
}

MtmErrorCode removeRoom(EscapeSystem sys, TechnionFaculty faculty, int id) {
	if( sys->rooms == NULL ) return MTM_INVALID_PARAMETER;
	if( faculty < 0 || faculty > 17 ) return MTM_INVALID_PARAMETER;
	if( id < 1 ) return MTM_INVALID_PARAMETER;
	//TODO not remove room with order
	SET_FOREACH(Room, val, sys->rooms) {
		if ( val->faculty == faculty && val->id == id ) {
			//TODO if is order
			if ( false ) {
				return MTM_RESERVATION_EXISTS;
			} else {
				//TODO remove all rooms
				setRemove(sys->rooms, val);
				return MTM_SUCCESS;
			}
		}
	}
	return MTM_ID_DOES_NOT_EXIST;
}



MtmErrorCode addOrder(EscapeSystem sys, char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl) {
	assert ( email != NULL );

	Order newOrder = malloc(sizeof(struct order_t));
	if ( newOrder == NULL) return MTM_OUT_OF_MEMORY;
	if ( email != NULL && emailValidity(email)) {
		newOrder->email = malloc(sizeof(char) * (strlen(email) + 1));
		if ( newOrder->email == NULL) {
			free(newOrder);
			return MTM_OUT_OF_MEMORY;
		}
		strcpy(newOrder->email, email);
	} else {
		free(newOrder);
		return MTM_INVALID_PARAMETER;
	}

	if ( time == NULL ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_INVALID_PARAMETER;
	} else if ( false ) { //TODO check time validity
		free(newOrder->email);
		free(newOrder);
		return MTM_INVALID_PARAMETER;
	}

	if ( returnEscaperFaculty( findEscaperByEmail(sys->escapers, email))  == UNKNOWN ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}
	Escaper escaper = findEscaperByEmail( sys->escapers, email );

	int hour = getHour( time );
	int daysFromToday = getDay( time );

	Room room = findRoom(sys->rooms, faculty, id);
	if ( room == NULL ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_ID_DOES_NOT_EXIST;
	}

	newOrder->faculty = faculty;
	newOrder->id = id;
	newOrder->price = calculatePriceOfOrder( sys->escapers, sys->rooms, email, room) * num_ppl;
	newOrder->hour = hour;
	newOrder->num_ppl = num_ppl;


	//
	if ( !checkIfRoomAvailable(sys->days, daysFromToday, hour, room) ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_ROOM_NOT_AVAILABLE;
	}

	if ( !checkIfEscaperAvailable(sys->days, daysFromToday, hour, escaper) ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_IN_ROOM;
	}
	/*
	if ( checkIfRoomAvailable(days, daysFromToday, hour, room) && checkIfEscaperAvailable(days, daysFromToday, hour, escaper) ) {

	} */

	addOrder2(sys->days, newOrder, daysFromToday);
	free(newOrder->email);
	free(newOrder);
	return MTM_SUCCESS;
}


MtmErrorCode addRecommendedOrder(EscapeSystem sys, char* email, int num_ppl ) {
	Order newOrder = malloc(sizeof(struct order_t));
	if ( newOrder == NULL) return MTM_OUT_OF_MEMORY;
	if ( email != NULL && emailValidity(email)) {
		newOrder->email = malloc(sizeof(char) * (strlen(email) + 1));
		if ( newOrder->email == NULL) {
			free(newOrder);
			return MTM_OUT_OF_MEMORY;
		}
		strcpy(newOrder->email, email);
	} else {
		free(newOrder);
		return MTM_INVALID_PARAMETER;
	}

	if ( returnEscaperFaculty( findEscaperByEmail(sys->escapers, email)) == UNKNOWN ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}
	Escaper escaper = findEscaperByEmail( sys->escapers, email );
	newOrder->num_ppl = num_ppl;

	//printf("\n number1: %d\n", setGetSize(rooms));
	MtmErrorCode result = MTM_SUCCESS;
	Set recommendedRooms = setCopy(sys->rooms);

	Set recommendedRooms2 = filterRoomSet( recommendedRooms, recommendByNumOfPplandDifficulty, num_ppl, escaper->typeSkill );
	if ( setGetSize(recommendedRooms2) != 1 ) {
		setDestroy(recommendedRooms);
		recommendedRooms = setCopy( recommendedRooms2 );
		setDestroy(recommendedRooms2);
		recommendedRooms2 = filterRoomSet( recommendedRooms, recommendByNearFaculty, escaper->faculty, 0 );
		if ( setGetSize(recommendedRooms2) != 1 ) {
			setDestroy(recommendedRooms);
			recommendedRooms = setCopy( recommendedRooms2 );
			setDestroy(recommendedRooms2);
			recommendedRooms2 = filterRoomSet( recommendedRooms, recommendByNearFaculty, 0, 0 );
			if ( setGetSize(recommendedRooms2) != 1 ) {
				setDestroy(recommendedRooms);
				recommendedRooms = setCopy( recommendedRooms2 );
				setDestroy(recommendedRooms2);
				recommendedRooms2 = filterRoomSet( recommendedRooms, recommendByNearId, 0, 0 );

			}
		}
	}

	//printf("\n number last: %d\n", setGetSize(recommendedRooms2));

	setDestroy(recommendedRooms);

	if ( setGetSize(recommendedRooms2) == 1) {
		Room room = setGetFirst(recommendedRooms2);
		newOrder->faculty=room->faculty;
		newOrder->id=room->id;
		newOrder->price = getTotalRoomPrice(room, escaper->faculty) * num_ppl;

		result = addFirstAvailableOrder(sys->days, newOrder, room, escaper);
		//TODO check return;
		setDestroy(recommendedRooms2);
		free(newOrder->email);
		free(newOrder);
		return result;
	} else {
		printf("why?!?");
	}

	free(newOrder->email);
	free(newOrder);

	return MTM_SUCCESS;
}




MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem system) {
	//List days = system->days;
	Day today = listGetFirst(system->days);
	List orders = today->dayOrders;
	mtmPrintDayHeader(outputChannel, today->dayNumber, listGetSize(orders));


	Escaper escaper = NULL;
	Room room = NULL;
	Order order = listGetFirst(orders);
	while ( order != NULL ) {
		//TODO check that escaper;
		escaper = findEscaperByEmail( system->escapers, order->email );
		//printUser(user);
		room = findRoom(system->rooms, order->faculty, order->id);
		//printRoom(room);
		//printOrder(order);
		mtmPrintOrder(outputChannel, escaper->email, escaper->typeSkill, escaper->faculty, room->email, room->faculty, room->id, order->hour, room->difficulty, order->num_ppl, order->price);
		addIncomeToFaculty(system->faculties, room->faculty, order->price );
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

	listSort( system->faculties, compareFacultyByIncomeAndId);
	mtmPrintFacultiesHeader(outputChannel, NUMBER_OF_FACULTIES, today->dayNumber, returnTotalRevenue(system->faculties));

	List bestList = returnBestNFaculties(system->faculties, NUMBER_OF_BEST);
	Faculty faculty = listGetFirst(bestList);
	while ( faculty != NULL ) {
		mtmPrintFaculty(outputChannel, faculty->id, faculty->income);
		faculty = listGetNext(bestList);
	}
	mtmPrintFacultiesFooter(outputChannel);
	listDestroy(bestList);

	return MTM_SUCCESS;
}





bool emailValidity(const char* email) {
	size_t len = strlen(email);
	int count = 0;
	for (int i = 0; i < len; i++) {
		if( email[i] == '@' ) count++;
	}
	return ( count == 1);
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

