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

	while ( fgets(line, MAX_NAME_LENG, filein) != NULL) {

		const char* firstNonSpace = line;
		while(*firstNonSpace != '\0' && isspace(*firstNonSpace)) {
			++firstNonSpace;
		}
		size_t len = strlen(firstNonSpace)+1;
		memmove(line, firstNonSpace, len);

		int numberOfCommand = convertStringToCommand( line );
		strtok(line, " \t");
		strtok(NULL, " \t");

		if ( numberOfCommand == 1 ) {
			char* email = strtok(NULL, " ");
			int faculty = atoi( strtok(NULL, " ") );
			addCompany(system, email, faculty );
		} else if ( numberOfCommand == 2 ) {
			char* email = strtok(NULL, " ");
			removeCompany(system, email);
		} else if ( numberOfCommand == 3 ) {
			char* email = strtok(NULL, " ");
			int id = atoi( strtok(NULL, " ") );
			int price = atoi( strtok(NULL, " ") );
			int num_ppl = atoi( strtok(NULL, " ") );
			char* working_hrs = strtok(NULL, " ");
			int difficulty = atoi( strtok(NULL, " ") );
			//TODO check return value
			addARoom(system, email, id, price, num_ppl, working_hrs, difficulty);
		} else if ( numberOfCommand == 4 ) {
			int faculty = atoi( strtok(NULL, " ") );
			int id = atoi( strtok(NULL, " ") );
			//TODO check return value
			removeARoom(system, faculty, id);
		} else if ( numberOfCommand == 5 ) {
			char* email = strtok(NULL, " ");
			int faculty = atoi( strtok(NULL, " ") );
			int skill_level = atoi( strtok(NULL, " ") );
			//TODO check return value
			addAnEscaper(system, email, faculty, skill_level);
		} else if ( numberOfCommand == 6 ) {
			char* email = strtok(NULL, " ");
			//TODO check return value
			removeAnEscaper(system, email);
		}  else if ( numberOfCommand == 7 ) {
			char* email = strtok(NULL, " ");
			int faculty = atoi( strtok(NULL, " ") );
			int id = atoi( strtok(NULL, " ") );
			char* time = strtok(NULL, " ");
			int num_ppl = atoi( strtok(NULL, " ") );
			//TODO check return value
			addAnOrder(system, email, faculty, id, time, num_ppl);
		} else if ( numberOfCommand == 8 ) {
			char* email = strtok(NULL, " ");
			int num_ppl = atoi( strtok(NULL, " ") );
			//TODO check return value
			addRecommendedOrder(system, email, num_ppl );
		} else if ( numberOfCommand == 9 ) {
			printf("\ndsfsd\n");
			//TODO check return value
			reportDay(fileout, system);
		} else if ( numberOfCommand == 10 ) {
			//TODO check return value
			reportBest(fileout, system);
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
	if ( newCompany == NULL ) return MTM_OUT_OF_MEMORY;
	if ( sys == NULL || !emailValidity(email) || !facultyValidity(faculty)) {
		free(newCompany);
		return MTM_INVALID_PARAMETER;
	}
/*	if ( faculty < 0 || faculty >= NUMBER_OF_FACULTIES ) {
		free(newCompany);
		return MTM_INVALID_PARAMETER;
	}*/

	createCompany(newCompany, email, faculty);

	//TODO check both escaper and company
	if( setIsIn( sys->companies, newCompany ) || findEscaperByEmail(sys, email) != NULL ) {
		freeCompany(newCompany);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	setAdd(sys->companies, newCompany);
	//free(newCompany->email);
	freeCompany(newCompany);
	return MTM_SUCCESS;
}

MtmErrorCode removeCompany(EscapeSystem sys, const char* email) {
	if( sys == NULL || !emailValidity(email) ) return MTM_INVALID_PARAMETER;

	Company company = findCompanyByEmail( sys , email );
	if ( company == NULL ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

	if ( isAnyRoomOfACompanyOrdered(sys, email) ) return MTM_RESERVATION_EXISTS;
	MtmErrorCode result = removeAllRoomsOfCompany(sys, email);
	if ( result != MTM_SUCCESS ) return result;

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

bool isAnyRoomOfACompanyOrdered(const EscapeSystem sys, const char* email) {
	SET_FOREACH(Room, val, sys->rooms) {
		if ( strcmp(val->email, email) == 0) {
			if ( IsARoomOrdered(sys, val->faculty, val->id) ) return true;
		}
	}
	return false;
}




MtmErrorCode addAnEscaper(EscapeSystem sys, const char* email, TechnionFaculty faculty, SkillLevel skillLevel) {
	Escaper newEscaper = malloc(sizeof(struct escaper_t));
	if ( newEscaper == NULL ) return MTM_OUT_OF_MEMORY;
	if ( sys == NULL || !emailValidity(email) || !facultyValidity(faculty) || !skillLevelValidation(skillLevel)) {
		free( newEscaper );
		return MTM_INVALID_PARAMETER;
	}


	//TODO check return value
	createEscaper(newEscaper, email, faculty, skillLevel);

	if( setIsIn( sys->escapers, newEscaper ) || findCompanyByEmail(sys, email) != NULL ) {
		freeCompany(newEscaper);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

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

MtmErrorCode removeAnEscaper(EscapeSystem sys, const char* email) {
	if( sys == NULL || !emailValidity(email) ) return MTM_INVALID_PARAMETER;

	Escaper escaper = findEscaperByEmail( sys, email );
	if ( escaper == NULL ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;

	markAsRemovedOrdersOfEscaper( sys, email );
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

bool isEscaperAvailable(const EscapeSystem sys, int daysFromToday, int hour, SetElement escaper) {
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



MtmErrorCode addARoom(EscapeSystem sys, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty) {
	Room newRoom = malloc(sizeof(struct room_t));
	if ( newRoom == NULL) return MTM_OUT_OF_MEMORY;
	//TODO working hours validity
	if ( sys == NULL || working_hrs == NULL ) {
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}
	if ( !emailValidity(email) || !skillLevelValidation(difficulty) ) {
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}

	Company company = findCompanyByEmail( sys, email);
	if ( company  == NULL ) {
		free(newRoom);
		return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
	}
	TechnionFaculty faculty = returnCompanyFaculty( company );
	if ( faculty == UNKNOWN ) {
		free(newRoom);
		return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
	}

	MtmErrorCode result = createRoom(newRoom, email, id, faculty, price, num_ppl, working_hrs, difficulty);
	if( result != MTM_SUCCESS ) {
		free(newRoom);
		return result;
	}

	if( setIsIn(sys->rooms, newRoom) ) {
		freeRoom(newRoom);
		return MTM_ID_ALREADY_EXIST;
	}

	//TODO check return value
	setAdd(sys->rooms, newRoom);
	addARoomToCompany(company);

	freeRoom(newRoom);
	return MTM_SUCCESS;
}

MtmErrorCode removeARoom(EscapeSystem sys, TechnionFaculty faculty, int id) {
	if( sys == NULL || !facultyValidity(faculty) || id < 1 ) return MTM_INVALID_PARAMETER;
	SET_FOREACH(Room, val, sys->rooms) {
		if ( val->faculty == faculty && val->id == id ) {
			if ( IsARoomOrdered(sys, faculty, id) ) {
				return MTM_RESERVATION_EXISTS;
			} else {
				setRemove(sys->rooms, val);
				return MTM_SUCCESS;
			}
		}
	}
	return MTM_ID_DOES_NOT_EXIST;
}

MtmErrorCode removeAllRoomsOfCompany(EscapeSystem sys, const char* email) {
	if ( sys == NULL || !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	MtmErrorCode result;
	SET_FOREACH(Room, val, sys->rooms) {
		if ( strcmp(val->email, email) == 0) {
			result = removeARoom(sys, val->faculty, val->id);
			if ( result != MTM_SUCCESS ) return result;
		}
	}
	return MTM_SUCCESS;
}

SetElement findRoom(const EscapeSystem sys, TechnionFaculty faculty, int id) {
	SET_FOREACH(Room, val, sys->rooms) {
		if ( val->faculty == faculty && val->id == id ) {
			return val;
		}
	}
	return NULL;
}

Room findRecommendedRoom(const EscapeSystem sys, const Escaper escaper, int  num_ppl) {
	Set recommendedRooms = NULL;
	Set recommendedRooms2 = filterRoomSet( sys->rooms, filterByNumOfPplandDifficulty, num_ppl, escaper->typeSkill );
	if ( setGetSize(recommendedRooms2) != 1 ) {
		setDestroy(recommendedRooms);
		recommendedRooms = setCopy( recommendedRooms2 );
		setDestroy(recommendedRooms2);
		recommendedRooms2 = filterRoomSet( recommendedRooms, filterByNearFaculty, escaper->faculty, 0 );
		if ( setGetSize(recommendedRooms2) != 1 ) {
			setDestroy(recommendedRooms);
			recommendedRooms = setCopy( recommendedRooms2 );
			setDestroy(recommendedRooms2);
			recommendedRooms2 = filterRoomSet( recommendedRooms, filterByNearFaculty, 0, 0 );
			if ( setGetSize(recommendedRooms2) != 1 ) {
				setDestroy(recommendedRooms);
				recommendedRooms = setCopy( recommendedRooms2 );
				setDestroy(recommendedRooms2);
				recommendedRooms2 = filterRoomSet( recommendedRooms, filterByNearId, 0, 0 );
			}
		}
	}
	Room room = copyRoom(setGetFirst(recommendedRooms2));
	setDestroy(recommendedRooms);
	setDestroy(recommendedRooms2);

	return room;

}

bool isRoomAvailable(const EscapeSystem sys, int daysFromToday, int hour, ListElement room) {
	if ( ((Room)room)->from_hrs > hour || ((Room)room)->to_hrs < hour ) return false;

	Day day = listGetFirst(sys->days);

	for(int i = 0; i < daysFromToday; i++ ) {
		day = listGetNext(sys->days);
		if ( day == NULL ) return true;
	}
	List orders = day->dayOrders;
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
	long int minValue = -1, tempValue;
	Set recommendedRooms = setCreate(copyRoom, freeRoom, compareRooms);
	while ( room != NULL ) {
		tempValue = recommendSetElement( room, key1, key2);
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




MtmErrorCode addAnOrder(EscapeSystem sys, const char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl) {
	Order newOrder = malloc(sizeof(struct order_t));
	if ( newOrder == NULL) return MTM_OUT_OF_MEMORY;
	if ( sys == NULL || !emailValidity(email) || !timeValidation(time) || !idValidation(id) || !facultyValidity(faculty)) {
		free(newOrder);
		return MTM_INVALID_PARAMETER;
	}

	Escaper escaper = findEscaperByEmail( sys, email );
	TechnionFaculty escaperFaculty = returnEscaperFaculty( escaper);
	Room room = findRoom(sys, faculty, id);
	int hour = convertHourStringToInt( time );
	int daysFromToday = convertDayStringToInt( time );

	if ( escaper == NULL || escaperFaculty == UNKNOWN ) {
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	} else if ( room == NULL ) {
		free(newOrder);
		return MTM_ID_DOES_NOT_EXIST;
	} else if ( !isRoomAvailable(sys, daysFromToday, hour, room) ) {
		free(newOrder);
		return MTM_ROOM_NOT_AVAILABLE;
	} else 	if ( !isEscaperAvailable(sys, daysFromToday, hour, escaper) ) {
		free(newOrder);
		return MTM_CLIENT_IN_ROOM;
	}

	MtmErrorCode result = createOrder(newOrder, email, faculty, id, calculatePriceOfOrder(room, escaperFaculty, num_ppl), num_ppl, hour );
	if ( result != MTM_SUCCESS ) {
		free(newOrder);
		return result;
	}

	Day day = returnADayFromToday(sys, daysFromToday);
	List orders = day->dayOrders;
	listInsertFirst(orders, newOrder);

	freeOrder(newOrder);
	return MTM_SUCCESS;
}

MtmErrorCode addRecommendedOrder(EscapeSystem sys, char* email, int num_ppl ) {
	Order newOrder = malloc(sizeof(struct order_t));
	if ( newOrder == NULL) return MTM_OUT_OF_MEMORY;
	if ( sys == NULL || !emailValidity(email) ) {
		free(newOrder);
		return MTM_INVALID_PARAMETER;
	}

	Escaper escaper = findEscaperByEmail( sys, email );
	if ( returnEscaperFaculty( escaper ) == UNKNOWN ) {
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}

	if ( setGetSize(sys->rooms) == 0 ) {
		free(newOrder);
		return MTM_NO_ROOMS_AVAILABLE;
	}

	Room room = findRecommendedRoom(sys, escaper, num_ppl);

	if ( room != NULL ) {
		int price = calculatePriceOfOrder(room, escaper->faculty, num_ppl);

		MtmErrorCode result = createOrder(newOrder, email, room->faculty, room->id, price, num_ppl, 0 );
		if ( result != MTM_SUCCESS ) {
			freeRoom(room);
			free(newOrder);
			return result;
		}

		result = addFirstAvailableOrder(sys, newOrder, room, escaper);
		//TODO check return;

		freeOrder(newOrder);
		freeRoom(room);
		return result;
	}

	freeOrder(newOrder);
	return MTM_SUCCESS;
}

MtmErrorCode addFirstAvailableOrder(EscapeSystem sys, Order order, SetElement room, SetElement escaper ) {
	int daysFromToday = 0;
	while ( true ) {
		for( int hour = 0; hour < 24; hour++) {
			if ( isRoomAvailable(sys, daysFromToday, hour, room) && isEscaperAvailable(sys, daysFromToday, hour, escaper) ) {
				setOrderHour(order, hour);
				Day day = returnADayFromToday(sys, daysFromToday);

				List orders = day->dayOrders;
				listInsertFirst(orders, order);
				return MTM_SUCCESS;
			}
		}
		daysFromToday++;
	}
	return MTM_SUCCESS;
}

bool IsARoomOrdered(const EscapeSystem sys, TechnionFaculty faculty, int id) {
	LIST_FOREACH(Day, dayVal, sys->days) {
		LIST_FOREACH(Order, orderVal, dayVal->dayOrders) {
			if ( orderVal->faculty == faculty && orderVal->id == id ) {
				return true;
			}
		}
	}
	return false;
}

Day returnADayFromToday(const EscapeSystem sys, int daysFromToday) {
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

MtmErrorCode markAsRemovedOrdersOfEscaper(EscapeSystem sys, const char* email ) {
	LIST_FOREACH(Day, dayVal, sys->days) {
		LIST_FOREACH(Order, orderVal, dayVal->dayOrders) {
			if ( strcmp(orderVal->email, email) == 0 ) {
				orderVal->faculty = UNKNOWN;
				strcpy(orderVal->email, "");
			}
		}
	}
	return MTM_SUCCESS;
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

List returnListOfBestNFaculties(List faculties, int number) {
	listSort(faculties, compareFacultyByIncomeAndId);
	//TODO check return;
	List newList = listCreate(copyFaculty, freeFaculty);
	ListElement faculty = listGetFirst( faculties );
	for(int i = 0; i < number; i++) {
		listInsertLast(newList, faculty);
		faculty = listGetNext( faculties );
	}
	return newList;
}

int returnTotalFacultiesRevenue(List faculties) {
	Faculty faculty = listGetFirst(faculties);
	int result = 0;
	while ( faculty != NULL ) {
		result += faculty->income;
		faculty = listGetNext(faculties);
	}
	return result;
}


MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem sys) {
	printf("\nreport run\n");
	Day today = listGetFirst(sys->days);
	List orders = today->dayOrders;
	mtmPrintDayHeader(outputChannel, today->dayNumber, listGetSize(orders));


	Escaper escaper = NULL;
	Room room = NULL;
	//TODO sort the orders
	listSort(orders , sortOrderByTimeFacultyId);
	Order order = listGetFirst(orders);
	while ( order != NULL ) {
		//TODO check that escaper;
		if ( order->faculty != UNKNOWN ) {
			escaper = findEscaperByEmail( sys, order->email );
			room = findRoom(sys, order->faculty, order->id);
			mtmPrintOrder(outputChannel, escaper->email, escaper->typeSkill, escaper->faculty, room->email, room->faculty, room->id, order->hour, room->difficulty, order->num_ppl, order->price);
			addIncomeToFaculty( findFacultyByNumber(sys->faculties, room->faculty), order->price );
		}
		order = listGetNext(orders);
	}
	mtmPrintDayFooter(outputChannel, today->dayNumber);

	if ( listGetSize(sys->days) == 1 ) {
		Day day = createDay(today->dayNumber+1);
		listInsertLast(sys->days, day);
		freeDay(day);
	}
	printAllDays(sys->days);
	listGetFirst(sys->days);
	listRemoveCurrent(sys->days);
	return MTM_SUCCESS;
}

MtmErrorCode reportBest(FILE* outputChannel, EscapeSystem system) {
	Day today = listGetFirst(system->days);

	listSort( system->faculties, compareFacultyByIncomeAndId);
	mtmPrintFacultiesHeader(outputChannel, NUMBER_OF_FACULTIES, today->dayNumber, returnTotalFacultiesRevenue(system->faculties));

	List bestList = returnListOfBestNFaculties(system->faculties, NUMBER_OF_BEST);
	Faculty faculty = listGetFirst(bestList);
	while ( faculty != NULL ) {
		mtmPrintFaculty(outputChannel, faculty->id, faculty->income);
		faculty = listGetNext(bestList);
	}
	mtmPrintFacultiesFooter(outputChannel);
	listDestroy(bestList);

	return MTM_SUCCESS;
}





