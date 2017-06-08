/*
 * mtm_escape.c
 *
 *  Created on: May 27, 2017
 *      Author: master
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "system.h"


#define MAX_NAME_LENG 200
#define MAX_COMMAND_LENG 7
#define NUMBER_OF_BEST 3


const int NUMBER_OF_FACULTIES = UNKNOWN;




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
	//TODO check return value
	createSystem(system);



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
			free( temp );

		}
	}

	destroySystem(system);

	fclose(fileout);
	fclose(filein);
	return 0;
}

MtmErrorCode createSystem(EscapeSystem sys) {
	assert(sys != NULL);
			//TODO test all return values
	sys->escapers = setCreate(copyEscaper, freeEscaper, compareEscapers);
	sys->companies = setCreate(copyCompany, freeCompany, compareCompanies);
	sys->rooms = setCreate(copyRoom, freeRoom, compareRooms);
	sys->days = createDays();
	sys->faculties = createFaculties(NUMBER_OF_FACULTIES);

	return MTM_SUCCESS;
}

MtmErrorCode destroySystem(EscapeSystem sys) {
	listDestroy(sys->days);
	listDestroy(sys->faculties);
	setDestroy(sys->rooms);
	setDestroy(sys->escapers);
	setDestroy(sys->companies);
	free(sys);
	return MTM_SUCCESS;
}



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

	Company company = findCompanyByEmail( sys , email );
	if ( company == NULL ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

	//TODO not remove company with order
	//TODO remove all rooms of the company
	setRemove(sys->companies , company);
	return MTM_SUCCESS;
}

SetElement findCompanyByEmail(const EscapeSystem sys, const char* email ) {
	if( sys->companies == NULL || email == NULL ) return NULL;
	SET_FOREACH(Company, val, sys->companies) {
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

	Escaper escaper = findEscaperByEmail( sys, email );
	if ( escaper == NULL || escaper->typeSkill == 0 ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;

	//TODO remove all his orders
	setRemove(sys->escapers, escaper);
	return MTM_SUCCESS;
}

SetElement findEscaperByEmail( const EscapeSystem sys, const char* email ) {
	if( sys == NULL || email == NULL ) return NULL;
	SET_FOREACH(Escaper, val, sys->escapers) {
		if ( strcmp(val->email, email) == 0) {
			return val;
		}
	}
	return NULL;
}

bool checkIfEscaperAvailable(const EscapeSystem sys, int daysFromToday, int hour, SetElement escaper) {
	Day day = listGetFirst(sys->days);
	for(int i = 0; i < daysFromToday; i++ ) {
		day = listGetNext(sys->days);
		if ( day == NULL ) return true;
	}
	List orders = day->dayOrders;
	List ordersOfEscaper = listFilter(orders, filterOrderByEscaper, ((Escaper)escaper)->email);
	Order order = listGetFirst(ordersOfEscaper);
	for(int i = 0; i < listGetSize(ordersOfEscaper); i++) {
		if ( order->hour == hour ) {
			listDestroy(ordersOfEscaper);
			return false;
		}
	}
	listDestroy(ordersOfEscaper);
	return true;
}



MtmErrorCode addRoom(EscapeSystem sys, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty) {
	if ( sys == NULL ) return MTM_INVALID_PARAMETER;
	if ( email == NULL || !emailValidity(email) )  return MTM_INVALID_PARAMETER;


	TechnionFaculty faculty = returnCompanyFaculty( findCompanyByEmail( sys, email) );

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

SetElement findRoom(const EscapeSystem sys, TechnionFaculty faculty, int id) {
	SET_FOREACH(Room, val, sys->rooms) {
		if ( val->faculty == faculty && val->id == id ) {
			return val;
		}
	}
	return NULL;
}

bool checkIfRoomAvailable(const EscapeSystem sys, int daysFromToday, int hour, ListElement room) {
	if ( ((Room)room)->from_hrs > hour || ((Room)room)->to_hrs < hour ) return false;

	Day day = listGetFirst(sys->days);

	for(int i = 0; i < daysFromToday; i++ ) {
		day = listGetNext(sys->days);
		if ( day == NULL ) return true;
	}
	List orders = day->dayOrders;
	//printRoom(((Room)room));
	//printAllOrders(orders);
	List ordersOfFaculty = listFilter(orders, filterOrderByFaculty, &(((Room)room)->faculty));
	List ordersOfRoom = listFilter(ordersOfFaculty, filterOrderById, &(((Room)room)->id));
	listDestroy(ordersOfFaculty);
	Order order = listGetFirst(ordersOfRoom);
	//TODO check working hours
	for(int i = 0; i < listGetSize(ordersOfRoom); i++) {
		if ( order->hour == hour ) {
			listDestroy(ordersOfRoom);
			return false;
		}
	}
	listDestroy(ordersOfRoom);
	return true;
}

Set filterRoomSet(const Set rooms, RecommendSetElement recommendSetElement, SetKey key1, SetKey key2 ) {
	Room room = setGetFirst(rooms);
	//User user = findUserFromEmail( users, email );
	long int minValue = -1, tempValue;
	Set recommendedRooms = setCreate(copyRoom, freeRoom, compareRooms);
	while ( room != NULL ) {
		tempValue = recommendSetElement( room, key1, key2);
		//tempValue = ( (pow(room->num_ppl-num_ppl,2) + (pow(room->difficulty - user->typeSkill,2 )) );
		if ( tempValue < minValue || minValue == -1) {
			minValue = tempValue;
			setClear(recommendedRooms);
			setAdd(recommendedRooms, room);
		} else if ( tempValue == minValue ) {
			setAdd(recommendedRooms, room);
		}
		room = setGetNext(rooms);
	}
	return recommendedRooms;
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

	Escaper escaper = findEscaperByEmail( sys, email );

	if ( returnEscaperFaculty( escaper)  == UNKNOWN ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}

	int hour = getHour( time );
	int daysFromToday = getDay( time );

	Room room = findRoom(sys, faculty, id);
	if ( room == NULL ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_ID_DOES_NOT_EXIST;
	}

	newOrder->faculty = faculty;
	newOrder->id = id;
	TechnionFaculty escaperFaculty = returnEscaperFaculty( findEscaperByEmail(sys, email));

	newOrder->price = calculatePriceOfOrder(room, escaperFaculty, num_ppl);
	newOrder->hour = hour;
	newOrder->num_ppl = num_ppl;


	//
	if ( !checkIfRoomAvailable(sys, daysFromToday, hour, room) ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_ROOM_NOT_AVAILABLE;
	}

	if ( !checkIfEscaperAvailable(sys, daysFromToday, hour, escaper) ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_IN_ROOM;
	}
	/*
	if ( checkIfRoomAvailable(days, daysFromToday, hour, room) && checkIfEscaperAvailable(days, daysFromToday, hour, escaper) ) {

	} */

	//addOrder2(sys->days, newOrder, daysFromToday);

	//addOrder2 was start here

	/*
	Day day = listGetFirst(sys->days);
	bool endOfList = false;
	int i = 0;
	while ( !endOfList && i < daysFromToday ) {
		day = listGetNext(sys->days);
		if ( day == NULL ) {
			endOfList = true;
			break;
		}
		i++;
	}
	while ( i < daysFromToday ) {
		Day newDay = createDay(i+1);
		if ( newDay == NULL ) {
			freeDay(newDay);
			return MTM_OUT_OF_MEMORY;
		}
		listInsertLast(sys->days, newDay);
		freeDay(newDay);
		i++;
	}
	if ( endOfList ) {
		day = listGetFirst(sys->days);
		for (int i = 0; i < daysFromToday; i++ ) {
			day = listGetNext(sys->days);
		}
	}*/
	Day day = returnDayOfOrder(sys, daysFromToday);
	List orders = day->dayOrders;
	listInsertFirst(orders, newOrder);
	//addOrder2 was end here

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

	Escaper escaper = findEscaperByEmail( sys, email );
	if ( returnEscaperFaculty( escaper ) == UNKNOWN ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}

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

		result = addFirstAvailableOrder(sys, newOrder, room, escaper);
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

MtmErrorCode addFirstAvailableOrder(EscapeSystem sys, ListElement order, SetElement room, SetElement escaper ) {
	//printRoom(room);
	//return MTM_SUCCESS;

	bool done = false;
	int daysFromToday = 0;

	while ( !done ) {
		for( int hour = 0; hour < 24; hour++) {
			if ( checkIfRoomAvailable(sys, daysFromToday, hour, room) && checkIfEscaperAvailable(sys, daysFromToday, hour, escaper) ) {
				((Order)order)->hour = hour;
				//addOrder2 was start here
				Day day = returnDayOfOrder(sys, daysFromToday);

				List orders = day->dayOrders;
				listInsertFirst(orders, order);
				return MTM_SUCCESS;
				//addOrder2 was end here
			}
		}
		daysFromToday++;
	}
	return MTM_SUCCESS;
}

Day returnDayOfOrder(const EscapeSystem sys, int daysFromToday) {
	Day day = listGetFirst(sys->days);
	bool endOfList = false;
	int i = 0;
	while ( !endOfList && i < daysFromToday ) {
		day = listGetNext(sys->days);
		if ( day == NULL ) {
			endOfList = true;
			break;
		}
		i++;
	}
	while ( i < daysFromToday ) {
		Day newDay = createDay(i+1);
		if ( newDay == NULL ) {
			freeDay(newDay);
			return MTM_OUT_OF_MEMORY;
		}
		listInsertLast(sys->days, newDay);
		freeDay(newDay);
		i++;
	}
	if ( endOfList ) {
		day = listGetFirst(sys->days);
		for (int i = 0; i < daysFromToday; i++ ) {
			day = listGetNext(sys->days);
		}
	}
	return day;
}



List createFaculties(int numberOfFaculties) {
	List faculties = listCreate(copyFaculty, freeFaculty);
	if ( faculties == NULL ) return NULL;

	Faculty newFaculty = malloc(sizeof(struct faculty_t));

	for( int i = 0; i < numberOfFaculties; i++) {
		newFaculty->id = i;
		newFaculty->income = 0;
		listInsertFirst(faculties, newFaculty);
	}
	free(newFaculty);
	return faculties;
}


Faculty findFacultyByNumber(List Faculties, TechnionFaculty facultyNumber) {
	Faculty faculty = listGetFirst(Faculties);
	while ( faculty != NULL ) {

		if ( faculty->id == facultyNumber ) {
			return faculty;
		}
		faculty = listGetNext(Faculties);
	}
	return NULL;
}



MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem sys) {
	//List days = system->days;
	Day today = listGetFirst(sys->days);
	List orders = today->dayOrders;
	mtmPrintDayHeader(outputChannel, today->dayNumber, listGetSize(orders));


	Escaper escaper = NULL;
	Room room = NULL;
	Order order = listGetFirst(orders);
	while ( order != NULL ) {
		//TODO check that escaper;
		escaper = findEscaperByEmail( sys, order->email );
		//printUser(user);
		room = findRoom(sys, order->faculty, order->id);
		//printRoom(room);
		//printOrder(order);
		mtmPrintOrder(outputChannel, escaper->email, escaper->typeSkill, escaper->faculty, room->email, room->faculty, room->id, order->hour, room->difficulty, order->num_ppl, order->price);
		addIncomeToFaculty( findFacultyByNumber(sys->faculties, room->faculty), order->price );
		//addIncomeToFaculty(sys->faculties, room->faculty, order->price );
		order = listGetNext(orders);
	}
	mtmPrintDayFooter(outputChannel, today->dayNumber);

	if ( listGetSize(sys->days) == 1 ) {
		Day day = createDay(today->dayNumber+1);
		listInsertLast(sys->days, day);
		freeDay(day);
	}

	listRemoveCurrent(sys->days);
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



