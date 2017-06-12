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



#define MAX_COMMAND_LENG 7
#define NUMBER_OF_BEST 3




MtmErrorCode createSystem(EscapeSystem sys) {
	if ( sys == NULL ) return MTM_NULL_PARAMETER;
	sys->escapers = setCreate(copyEscaper, freeEscaper, compareEscapers);
	sys->companies = setCreate(copyCompany, freeCompany, compareCompanies);
	sys->rooms = setCreate(copyRoom, freeRoom, compareRooms);
	sys->days = createDays();
	sys->faculties = createFaculties(NUMBER_OF_FACULTIES);

	return MTM_SUCCESS;
}

MtmErrorCode destroySystem(EscapeSystem sys) {
	if ( sys == NULL ) return MTM_NULL_PARAMETER;
	listDestroy(sys->days);
	listDestroy(sys->faculties);
	setDestroy(sys->rooms);
	setDestroy(sys->escapers);
	setDestroy(sys->companies);
	free(sys);
	return MTM_SUCCESS;
}

MtmErrorCode inputChannelSelector(int argc, char* argv[], FILE** channelIn, FILE** channelOut, FILE** channelErr ) {
	if ( argc == 5 ) {
		return sellectBothFiles(argv, channelIn, channelOut, channelErr);
	} else if ( argc == 3 ) {
		return sellectOneOfTheFiles(argv, channelIn, channelOut, channelErr);
	} else if ( argc == 1 ) {
		*channelIn = stdin;
		*channelOut = stdout;
		*channelErr = stderr;
		return MTM_SUCCESS;
	}
	return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}

MtmErrorCode sellectBothFiles(char* argv[], FILE** channelIn, FILE** channelOut, FILE** channelErr) {
	char* inFile;
	char* outFile;
	char* errFile;
	if ( strcmp(argv[1],"-i") == 0 && strcmp(argv[3],"-o") == 0) {
		inFile = addInSuffix( argv[2] );
		if ( inFile == NULL ) return MTM_OUT_OF_MEMORY;
		outFile = addOutSuffix( argv[4] );
		if ( outFile == NULL ) {
			free(inFile);
			return MTM_OUT_OF_MEMORY;
		}
		errFile = addErrSuffix( argv[4] );
		if ( errFile == NULL ) {
			free(inFile);
			free(outFile);
			return MTM_OUT_OF_MEMORY;
		}
	} else if ( strcmp(argv[1],"-o") == 0 && strcmp(argv[3],"-i") == 0 ) {
		inFile = addInSuffix( argv[4] );
		if ( inFile == NULL ) return MTM_OUT_OF_MEMORY;
		outFile = addOutSuffix( argv[2] );
		if ( outFile == NULL ) {
			free(inFile);
			return MTM_OUT_OF_MEMORY;
		}
		errFile = addErrSuffix( argv[2] );
		if ( errFile == NULL ) {
			free(inFile);
			free(outFile);
			return MTM_OUT_OF_MEMORY;
		}
	} else {
		return MTM_INVALID_COMMAND_LINE_PARAMETERS;
	}
	MtmErrorCode result = openAllFiles(inFile, outFile, errFile, channelIn, channelOut, channelErr);
	freeAllNames(inFile, outFile, errFile);
	return result;
}

MtmErrorCode sellectOneOfTheFiles(char* argv[], FILE** channelIn, FILE** channelOut, FILE** channelErr) {
	if ( strcmp(argv[1],"-i") == 0 ) {
		char* inFile = addInSuffix( argv[2] );
		if ( inFile == NULL ) return MTM_OUT_OF_MEMORY;
		*channelIn = fopen(inFile, "r");
		if ( *channelIn == NULL ) {
			free(inFile);
			return MTM_CANNOT_OPEN_FILE;
		}
		free(inFile);
		*channelOut = stdout;
		*channelErr = stderr;
	} else if ( strcmp(argv[1],"-o") == 0 ) {
		char* outFile = addOutSuffix( argv[2] );
		if ( outFile == NULL ) return MTM_OUT_OF_MEMORY;
		char* errFile = addErrSuffix( argv[2] );
		if ( outFile == NULL ) {
			free(outFile);
			return MTM_OUT_OF_MEMORY;
		}
		*channelOut = fopen(outFile, "w");
		if ( *channelOut == NULL ) {
			free(outFile);
			free(errFile);
			return MTM_CANNOT_OPEN_FILE;
		}
		*channelErr = fopen(errFile, "w");
		if ( *channelErr == NULL ) {
			fclose(*channelOut);
			free(outFile);
			free(errFile);
			return MTM_CANNOT_OPEN_FILE;
		}
		free(outFile);
		free(errFile);
		*channelIn = stdin;
	} else  {
		return MTM_INVALID_COMMAND_LINE_PARAMETERS;
	}
	return MTM_SUCCESS;
}


MtmErrorCode openAllFiles(const char *inFile, const  char *outFile, const  char *errFile, FILE** channelIn, FILE** channelOut, FILE** channelErr) {
	*channelIn = fopen(inFile, "r");
	if ( *channelIn == NULL ) {
		return MTM_CANNOT_OPEN_FILE;
	}
	*channelOut = fopen(outFile, "w");
	if ( *channelOut == NULL ) {
		fclose(*channelIn);
		return MTM_CANNOT_OPEN_FILE;
	}
	*channelErr = fopen(errFile, "w");
	if ( *channelErr == NULL ) {
		fclose(*channelIn);
		fclose(*channelOut);
		return MTM_CANNOT_OPEN_FILE;
	}
	return MTM_SUCCESS;
}

char* addInSuffix(const char *s){
    char *result = malloc(sizeof(char) * (strlen(s)+4));//+1 for the zero-terminator
    if ( result == NULL ) return NULL;
    strcpy(result, s);
    strcat(result, ".in");
    return result;
}

char* addOutSuffix(const char *s){
    char *result = malloc(sizeof(char) * (strlen(s)+5));//+1 for the zero-terminator
    if ( result == NULL ) return NULL;
    strcpy(result, s);
    strcat(result, ".out");
    return result;
}

char* addErrSuffix(const char *s){
    char *result = malloc(sizeof(char) * (strlen(s)+5));//+1 for the zero-terminator
    if ( result == NULL ) return NULL;
    strcpy(result, s);
    strcat(result, ".err");
    return result;
}

void freeAllNames(char *in, char *out, char *err) {
	free(in);
	free(out);
	free(err);
}



MtmErrorCode addCompany(EscapeSystem sys, const char* email, TechnionFaculty faculty) {
	Company newCompany = malloc(sizeof(struct company_t));
	if ( newCompany == NULL ) return MTM_OUT_OF_MEMORY;
	if ( sys == NULL || !emailValidation(email) || !facultyValidation(faculty)) {
		free(newCompany);
		return MTM_INVALID_PARAMETER;
	}

	createCompany(newCompany, email, faculty);

	if( setIsIn( sys->companies, newCompany ) || findEscaperByEmail(sys, email) != NULL ) {
		freeCompany(newCompany);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	setAdd(sys->companies, newCompany);
	freeCompany(newCompany);
	return MTM_SUCCESS;
}

MtmErrorCode removeCompany(EscapeSystem sys, const char* email) {
	if( sys == NULL || !emailValidation(email) ) return MTM_INVALID_PARAMETER;

	Company company = findCompanyByEmail( sys , email );
	if ( company == NULL ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

	if ( isAnyRoomOfACompanyOrdered(sys, email) ) return MTM_RESERVATION_EXISTS;
	MtmErrorCode result = removeAllRoomsOfCompany(sys, email);
	if ( result != MTM_SUCCESS ) return result;

	setRemove(sys->companies , company);
	return MTM_SUCCESS;
}

Company findCompanyByEmail(const EscapeSystem sys, const char* email ) {
	if ( email == NULL ) return NULL;
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




MtmErrorCode addEscaper(EscapeSystem sys, const char* email, TechnionFaculty faculty, SkillLevel skillLevel) {
	Escaper newEscaper = malloc(sizeof(struct escaper_t));
	if ( newEscaper == NULL ) return MTM_OUT_OF_MEMORY;
	if ( sys == NULL || !emailValidation(email) || !facultyValidation(faculty) || !skillLevelValidation(skillLevel)) {
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

MtmErrorCode removeEscaper(EscapeSystem sys, const char* email) {
	if( sys == NULL || !emailValidation(email) ) return MTM_INVALID_PARAMETER;
	Escaper escaper = findEscaperByEmail( sys, email );
	if ( escaper == NULL ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	removedOrdersOfEscaper( sys, email );
	setRemove(sys->escapers, escaper);
	return MTM_SUCCESS;
}

Escaper findEscaperByEmail( const EscapeSystem sys, const char* email ) {
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
	if ( sys == NULL || working_hrs == NULL || !idValidation(id) || !emailValidation(email) ) {
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}
	int from =  fromHour(working_hrs);
	int to =  toHour(working_hrs);

	if ( !hoursValidation (from, to) || !skillLevelValidation(difficulty) || !priceValidation(price) || !numberOfPeoplepriceValidation(num_ppl) ) {
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
	MtmErrorCode result = createRoom(newRoom, email, id, faculty, price, num_ppl, from, to, difficulty);
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
	//addARoomToCompany(company);
	freeRoom(newRoom);
	return MTM_SUCCESS;
}

MtmErrorCode removeARoom(EscapeSystem sys, TechnionFaculty faculty, int id) {
	if( sys == NULL || !facultyValidation(faculty) || id < 1 ) return MTM_INVALID_PARAMETER;
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
	if ( sys == NULL || !emailValidation(email) ) return MTM_INVALID_PARAMETER;
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
	while ( order != NULL ) {
		if ( order->hour == hour ) {
			listDestroy(ordersOfRoom);
			return false;
		}
		order = listGetNext(ordersOfRoom);
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
	if ( sys == NULL || !emailValidation(email) || !timeValidation(time) || !idValidation(id) || !facultyValidation(faculty) || !numberOfPeoplepriceValidation (num_ppl)) {
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
	} else 	if ( !isEscaperAvailable(sys, daysFromToday, hour, escaper) ) {
		free(newOrder);
		return MTM_CLIENT_IN_ROOM;
	} else if ( !isRoomAvailable(sys, daysFromToday, hour, room) ) {
		free(newOrder);
		return MTM_ROOM_NOT_AVAILABLE;
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
	if ( sys == NULL || !emailValidation(email) ) {
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

MtmErrorCode removedOrdersOfEscaper(EscapeSystem sys, const char* email ) {
	Day day = listGetFirst(sys->days);
	Order order;
	while( day != NULL ) {
		order = listGetFirst(day->dayOrders);
		while( order != NULL ) {
			if ( strcmp(order->email, email) == 0 ) {
				listRemoveCurrent(day->dayOrders);
				order = listGetFirst(day->dayOrders);
			} else {
				order = listGetNext(day->dayOrders);
			}
		}
		day = listGetNext(sys->days);
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
	Day today = listGetFirst(sys->days);
	List orders = today->dayOrders;
	mtmPrintDayHeader(outputChannel, today->dayNumber, listGetSize(orders));

	Escaper escaper = NULL;
	Room room = NULL;
	listSort(orders , sortOrderByTimeFacultyId);
	Order order = listGetFirst(orders);
	while ( order != NULL ) {
		//TODO check that escaper;
		escaper = findEscaperByEmail( sys, order->email );
		room = findRoom(sys, order->faculty, order->id);
		mtmPrintOrder(outputChannel, escaper->email, escaper->typeSkill, escaper->faculty, room->email, room->faculty, room->id, order->hour, room->difficulty, order->num_ppl, order->price);
		addIncomeToFaculty( findFacultyByNumber(sys->faculties, room->faculty), order->price );
		order = listGetNext(orders);
	}
	mtmPrintDayFooter(outputChannel, today->dayNumber);

	if ( listGetSize(sys->days) == 1 ) {
		Day day = createDay(today->dayNumber+1);
		listInsertLast(sys->days, day);
		freeDay(day);
	}
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





