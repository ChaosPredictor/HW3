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



MtmErrorCode createSystem(EscapeSystem system) {
	if ( system == NULL ) return MTM_NULL_PARAMETER;
	system->escapers = setCreate(copyEscaper, freeEscaper, compareEscapers);
	if( system->escapers == NULL ) return MTM_OUT_OF_MEMORY;
	system->companies = setCreate(copyCompany, freeCompany, compareCompanies);
	if( system->escapers == NULL ) {
		setDestroy(system->escapers);
		return MTM_OUT_OF_MEMORY;
	}
	system->rooms = setCreate(copyRoom, freeRoom, compareRooms);
	if( system->rooms == NULL ) {
		setDestroy(system->companies);
		setDestroy(system->escapers);
		return MTM_OUT_OF_MEMORY;
	}
	system->days = createDays();
	if( system->days == NULL ) {
		setDestroy(system->rooms);
		setDestroy(system->companies);
		setDestroy(system->escapers);
		return MTM_OUT_OF_MEMORY;
	}
	system->faculties = createFaculties(NUMBER_OF_FACULTIES);
	if( system->faculties == NULL ) {
		listDestroy(system->days);
		setDestroy(system->rooms);
		setDestroy(system->companies);
		setDestroy(system->escapers);
		return MTM_OUT_OF_MEMORY;
	}
	return MTM_SUCCESS;
}

MtmErrorCode destroySystem(EscapeSystem system) {
	if ( system == NULL ) return MTM_NULL_PARAMETER;
	listDestroy(system->days);
	listDestroy(system->faculties);
	setDestroy(system->rooms);
	setDestroy(system->escapers);
	setDestroy(system->companies);
	free(system);
	return MTM_SUCCESS;
}

MtmErrorCode channelSelectorFunction(int argc, char* argv[], FILE** channel_in,\
		FILE** channel_out ) {
	if ( argc == 5 ) {
		return readBothFiles(argv, channel_in, channel_out);
	} else if ( argc == 3 ) {
		return readOneOfTheFiles(argv, channel_in, channel_out);
	} else if ( argc == 1 ) {
		*channel_in = stdin;
		*channel_out = stdout;
		return MTM_SUCCESS;
	}
	return MTM_INVALID_COMMAND_LINE_PARAMETERS;
}

MtmErrorCode readBothFiles(char* argv[],FILE** channel_in,FILE** channel_out) {
	if ( strcmp(argv[1],"-i") == 0 && strcmp(argv[3],"-o") == 0) {
		*channel_in = fopen(argv[2], "r");
		if ( *channel_in == NULL ) return MTM_CANNOT_OPEN_FILE;
		*channel_out = fopen(argv[4], "w");
		if ( *channel_out == NULL ) {
			fclose(*channel_in);
			return MTM_CANNOT_OPEN_FILE;
		}
	} else if ( strcmp(argv[1],"-o") == 0 && strcmp(argv[3],"-i") == 0 ) {
		*channel_in = fopen(argv[4], "r");
		if ( *channel_in == NULL ) return MTM_CANNOT_OPEN_FILE;
		*channel_out = fopen(argv[2], "w");
		if ( *channel_out == NULL ) {
			fclose(*channel_in);
			return MTM_CANNOT_OPEN_FILE;
		}
	} else {
		return MTM_INVALID_COMMAND_LINE_PARAMETERS;
	}

	return MTM_SUCCESS;
}

MtmErrorCode readOneOfTheFiles(char* argv[], FILE** channel_in, FILE** \
		channel_out) {
	if ( strcmp(argv[2],"-i") == 0 || strcmp(argv[2],"-o") == 0) {
		return MTM_INVALID_COMMAND_LINE_PARAMETERS;
	} else if ( strcmp(argv[1],"-i") == 0 ) {
		*channel_in = fopen(argv[2], "r");
		if ( *channel_in == NULL ) return MTM_CANNOT_OPEN_FILE;
		*channel_out = stdout;
	} else if ( strcmp(argv[1],"-o") == 0 ) {
		*channel_out = fopen(argv[2], "w");
		if ( *channel_out == NULL ) return MTM_CANNOT_OPEN_FILE;
		*channel_in = stdin;
	} else  {
		return MTM_INVALID_COMMAND_LINE_PARAMETERS;
	}
	return MTM_SUCCESS;
}

MtmErrorCode addCompany(EscapeSystem system, const char* email, \
		TechnionFaculty faculty) {
	Company new_company = malloc(sizeof(struct company_t));
	if ( new_company == NULL ) return MTM_OUT_OF_MEMORY;
	if ( system == NULL || !emailValidation(email) || !facultyValidation(faculty)){
		free(new_company);
		return MTM_INVALID_PARAMETER;
	}

	MtmErrorCode result = createCompany(new_company, email, faculty);
	if ( result != MTM_SUCCESS ) {
		free( new_company );
		return result;
	}
	if( setIsIn( system->companies, new_company ) || \
			findEscaperByEmail(system, email) != NULL ) {
		freeCompany(new_company);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	SetResult set_result = setAdd(system->companies, new_company);
	freeCompany(new_company);
	if ( set_result == SET_OUT_OF_MEMORY) {
		return MTM_OUT_OF_MEMORY;
	} else if ( set_result == SET_ITEM_ALREADY_EXISTS ) {
		return MTM_EMAIL_ALREADY_EXISTS;
	}
	return MTM_SUCCESS;
}

MtmErrorCode removeCompany(EscapeSystem system, const char* email) {
	if( system == NULL|| !emailValidation(email) ) return MTM_INVALID_PARAMETER;

	Company company = findCompanyByEmail( system , email );
	if ( company == NULL ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;

	if (isAnyRoomOfACompanyOrdered(system,email)) return MTM_RESERVATION_EXISTS;
	MtmErrorCode result = removeAllRoomsOfCompany(system, email);
	if ( result != MTM_SUCCESS ) return result;

	setRemove(system->companies , company);
	return MTM_SUCCESS;
}

Company findCompanyByEmail(const EscapeSystem system, const char* email ) {
	if( system->companies == NULL || email == NULL ) return NULL;
	SET_FOREACH(Company, val, system->companies) {
		if ( strcmp(val->email, email) == 0) {
			return val;
		}
	}
	return NULL;
}

bool isAnyRoomOfACompanyOrdered(const EscapeSystem system, const char* email) {
	SET_FOREACH(Room, val, system->rooms) {
		if ( strcmp(val->email, email) == 0) {
			if ( IsRoomOrdered(system, val->faculty, val->id) ) return true;
		}
	}
	return false;
}




MtmErrorCode addEscaper(EscapeSystem system, const char* email, \
		TechnionFaculty faculty, SkillLevel skill_level) {
	Escaper new_escaper = malloc(sizeof(struct escaper_t));
	if ( new_escaper == NULL ) return MTM_OUT_OF_MEMORY;
	if ( system == NULL || !emailValidation(email) || !facultyValidation(faculty) \
			|| !skillLevelValidation(skill_level)) {
		free( new_escaper );
		return MTM_INVALID_PARAMETER;
	}
	MtmErrorCode result = createEscaper(new_escaper,email,faculty, skill_level);
	if ( result != MTM_SUCCESS ) {
		free( new_escaper );
		return result;
	}

	if( setIsIn( system->escapers, new_escaper ) || \
			findCompanyByEmail(system, email) != NULL ) {
		freeEscaper(new_escaper);
		return MTM_EMAIL_ALREADY_EXISTS;
	}

	SetResult set_result = setAdd(system->escapers, new_escaper);
	freeEscaper(new_escaper);
	if ( set_result == SET_OUT_OF_MEMORY) {
		return MTM_OUT_OF_MEMORY;
	} else if ( set_result == SET_NULL_ARGUMENT ) {
		return MTM_NULL_PARAMETER;
	} else if ( set_result == SET_ITEM_ALREADY_EXISTS ) {
		return MTM_EMAIL_ALREADY_EXISTS;
	}
	return MTM_SUCCESS;
}

MtmErrorCode removeEscaper(EscapeSystem system, const char* email) {
	if( system == NULL || !emailValidation(email) ) return MTM_INVALID_PARAMETER;
	Escaper escaper = findEscaperByEmail( system, email );
	if ( escaper == NULL ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	removedOrdersOfEscaper( system, email );
	setRemove(system->escapers, escaper);
	return MTM_SUCCESS;
}

Escaper findEscaperByEmail( const EscapeSystem system, const char* email ) {
	if( system == NULL || email == NULL ) return NULL;
	SET_FOREACH(Escaper, val, system->escapers) {
		if ( strcmp(val->email, email) == 0) {
			return val;
		}
	}
	return NULL;
}

bool isEscaperAvailable(const EscapeSystem system, int days_from_today, \
		int hour, SetElement escaper) {
	Day day = listGetFirst(system->days);
	for(int i = 0; i < days_from_today; i++ ) {
		day = listGetNext(system->days);
		if ( day == NULL ) return true;
	}
	List orders = day->dayOrders;
	List orders_of_escaper = listFilter(orders, filterOrderByEscaper, \
			((Escaper)escaper)->email);
	Order order = listGetFirst(orders_of_escaper);
	for(int i = 0; i < listGetSize(orders_of_escaper); i++) {
		if ( order->hour == hour ) {
			listDestroy(orders_of_escaper);
			return false;
		}
		order = listGetNext(orders_of_escaper);
	}
	listDestroy(orders_of_escaper);
	return true;
}



MtmErrorCode addRoom(EscapeSystem system, const char* email, int id, \
		int price, int num_ppl, char* working_hrs, int difficulty) {
	Room new_room = malloc(sizeof(struct room_t));
	if ( new_room == NULL) return MTM_OUT_OF_MEMORY;
	if ( system == NULL || working_hrs == NULL || !idValidation(id) \
			|| !emailValidation(email) ) {
		free(new_room);
		return MTM_INVALID_PARAMETER;
	}
	int from =  fromHour(working_hrs);
	int to =  toHour(working_hrs);
	if ( !hoursValidation (from, to) || !skillLevelValidation(difficulty) \
			|| !priceValidation(price) || \
			!numberOfPeoplepriceValidation(num_ppl) ) {
		free(new_room);
		return MTM_INVALID_PARAMETER;
	}
	Company company = findCompanyByEmail( system, email);
	if ( company  == NULL ) {
		free(new_room);
		return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
	}
	TechnionFaculty faculty = returnCompanyFaculty( company );
	if ( faculty == UNKNOWN ) {
		free(new_room);
		return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
	}
	MtmErrorCode result = createRoom(new_room, email, id, faculty, \
			price, num_ppl, from, to, difficulty);
	if( result != MTM_SUCCESS ) {
		free(new_room);
		return result;
	}
	if( setIsIn(system->rooms, new_room) ) {
		freeRoom(new_room);
		return MTM_ID_ALREADY_EXIST;
	}
	SetResult set_result = setAdd(system->rooms, new_room);
	freeRoom(new_room);
	if ( set_result == SET_OUT_OF_MEMORY) {
		return MTM_OUT_OF_MEMORY;
	} else if ( set_result == SET_ITEM_ALREADY_EXISTS ) {
		return MTM_ID_ALREADY_EXIST;
	}
	return MTM_SUCCESS;
}

MtmErrorCode removeRoom(EscapeSystem system, TechnionFaculty faculty, int id) {
	if( system == NULL || !facultyValidation(faculty) || id < 1 ) \
			return MTM_INVALID_PARAMETER;
	SET_FOREACH(Room, val, system->rooms) {
		if ( val->faculty == faculty && val->id == id ) {
			if ( IsRoomOrdered(system, faculty, id) ) {
				return MTM_RESERVATION_EXISTS;
			} else {
				setRemove(system->rooms, val);
				return MTM_SUCCESS;
			}
		}
	}
	return MTM_ID_DOES_NOT_EXIST;
}

MtmErrorCode removeAllRoomsOfCompany(EscapeSystem system, const char* email) {
	if (system == NULL || !emailValidation(email)) return MTM_INVALID_PARAMETER;
	MtmErrorCode result;
	SET_FOREACH(Room, val, system->rooms) {
		if ( strcmp(val->email, email) == 0) {
			result = removeRoom(system, val->faculty, val->id);
			if ( result != MTM_SUCCESS ) return result;
		}
	}
	return MTM_SUCCESS;
}

Room findRoom(const EscapeSystem system, TechnionFaculty faculty,int id) {
	if ( system == NULL ) return NULL;
	SET_FOREACH(Room, val, system->rooms) {
		if ( val->faculty == faculty && val->id == id ) {
			return val;
		}
	}
	return NULL;
}

Room findRecommendedRoom(const EscapeSystem system, const Escaper escaper, \
		int  num_ppl) {
	if ( system == NULL || escaper == NULL ) return NULL;
	Set recommended_rooms = NULL;
	Set recommended_rooms2 = findTheMostFitRooms( system->rooms, \
			filterByNumOfPplandDifficulty, num_ppl, escaper->typeSkill );
	if ( setGetSize(recommended_rooms2) != 1 ) {
		setDestroy(recommended_rooms);
		recommended_rooms = setCopy( recommended_rooms2 );
		setDestroy(recommended_rooms2);
		recommended_rooms2 = findTheMostFitRooms( recommended_rooms, \
				filterByNearFaculty, escaper->faculty, 0 );
		if ( setGetSize(recommended_rooms2) != 1 ) {
			setDestroy(recommended_rooms);
			recommended_rooms = setCopy( recommended_rooms2 );
			setDestroy(recommended_rooms2);
			recommended_rooms2 = findTheMostFitRooms( recommended_rooms, \
					filterByNearFaculty, 0, 0 );
			if ( setGetSize(recommended_rooms2) != 1 ) {
				setDestroy(recommended_rooms);
				recommended_rooms = setCopy( recommended_rooms2 );
				setDestroy(recommended_rooms2);
				recommended_rooms2 = findTheMostFitRooms( recommended_rooms, \
						filterByNearId, 0, 0 );
			}
		}
	}
	Room room = copyRoom(setGetFirst(recommended_rooms2));
	setDestroy(recommended_rooms);
	setDestroy(recommended_rooms2);

	return room;

}

bool isRoomAvailable(const EscapeSystem system, int days_from_today, int hour, \
		ListElement room) {
	if(((Room)room)->from_hrs > hour||((Room)room)->to_hrs <=hour) return false;

	Day day = listGetFirst(system->days);

	for(int i = 0; i < days_from_today; i++ ) {
		day = listGetNext(system->days);
		if ( day == NULL ) return true;
	}
	List orders = day->dayOrders;
	List orders_of_faculty = listFilter(orders, filterOrderByFaculty, \
			&(((Room)room)->faculty));
	List orders_of_room = listFilter(orders_of_faculty, filterOrderById, \
			&(((Room)room)->id));
	listDestroy(orders_of_faculty);
	Order order = listGetFirst(orders_of_room);
	while ( order != NULL ) {
		if ( order->hour == hour ) {
			listDestroy(orders_of_room);
			return false;
		}
		order = listGetNext(orders_of_room);
	}
	listDestroy(orders_of_room);
	return true;
}


Set findTheMostFitRooms(const Set rooms, RecommendSetElement recommendSetElement, \
		SetKey key1, SetKey key2 ) {
	if ( rooms == NULL ) return NULL;
	Room room_under_check = setGetFirst(rooms);
	long int suitability = -1, current_room_value; // as lower as better
	Set recommended_rooms = setCreate(copyRoom, freeRoom, compareRooms);
	while ( room_under_check != NULL ) {
		current_room_value = recommendSetElement( room_under_check, key1, key2);
		if ( current_room_value < suitability || suitability == -1) {
			suitability = current_room_value;
			setClear(recommended_rooms);
			setAdd(recommended_rooms, room_under_check);
		} else if ( current_room_value == suitability ) {
			setAdd(recommended_rooms, room_under_check);
		}
		room_under_check = setGetNext(rooms);
	}
	return recommended_rooms;
}




MtmErrorCode addOrder(EscapeSystem system,const char* email, TechnionFaculty \
		faculty, int id, const char* time, int num_ppl) {
	Order new_order = malloc(sizeof(struct order_t));
	if ( new_order == NULL) return MTM_OUT_OF_MEMORY;
	if ( system == NULL || !emailValidation(email) || !timeValidation(time) || \
			!idValidation(id) || !facultyValidation(faculty) || \
			!numberOfPeoplepriceValidation (num_ppl)) {
		free(new_order);
		return MTM_INVALID_PARAMETER;
	}

	Escaper escaper = findEscaperByEmail( system, email );
	TechnionFaculty escaper_faculty = returnEscaperFaculty( escaper);
	Room room = findRoom(system, faculty, id);
	int hour = convertHourStringToInt( time );
	int days_from_today = convertDayStringToInt( time );

	if ( escaper == NULL || escaper_faculty == UNKNOWN ) {
		free(new_order);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	} else if ( room == NULL ) {
		free(new_order);
		return MTM_ID_DOES_NOT_EXIST;
	} else if ( !isEscaperAvailable(system, days_from_today, hour, escaper) ) {
		free(new_order);
		return MTM_CLIENT_IN_ROOM;
	} else if ( !isRoomAvailable(system, days_from_today, hour, room) ) {
		free(new_order);
		return MTM_ROOM_NOT_AVAILABLE;
	}

	MtmErrorCode result = createOrder(new_order, email, faculty, id, \
			calculatePriceOfOrder(room, escaper_faculty, num_ppl),num_ppl,hour );
	if ( result != MTM_SUCCESS ) {
		free(new_order);
		return result;
	}

	Day day = returnDayFromToday(system, days_from_today);
	List orders = day->dayOrders;
	ListResult list_result = listInsertFirst(orders, new_order);
	if ( list_result == LIST_OUT_OF_MEMORY) {
		return MTM_OUT_OF_MEMORY;
	} else if ( list_result == LIST_NULL_ARGUMENT) {
		return MTM_NULL_PARAMETER;
	}
	freeOrder(new_order);
	return MTM_SUCCESS;
}

MtmErrorCode addRecommendedOrder(EscapeSystem system,char* email,int num_ppl ) {
	Order new_order = malloc(sizeof(struct order_t));
	if ( new_order == NULL) return MTM_OUT_OF_MEMORY;
	if ( system == NULL || !emailValidation(email) ) {
		free(new_order);
		return MTM_INVALID_PARAMETER;
	}

	Escaper escaper = findEscaperByEmail( system, email );
	if ( returnEscaperFaculty( escaper ) == UNKNOWN ) {
		free(new_order);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}

	if ( setGetSize(system->rooms) == 0 ) {
		free(new_order);
		return MTM_NO_ROOMS_AVAILABLE;
	}

	Room room = findRecommendedRoom(system, escaper, num_ppl);

	if ( room != NULL ) {
		int price = calculatePriceOfOrder(room, escaper->faculty, num_ppl);

		MtmErrorCode result = createOrder(new_order, email, room->faculty, \
				room->id, price, num_ppl, 0 );
		if ( result != MTM_SUCCESS ) {
			freeRoom(room);
			free(new_order);
			return result;
		}

		result = addFirstAvailableOrder(system, new_order, room, escaper);

		freeOrder(new_order);
		freeRoom(room);
		return result;
	}

	freeOrder(new_order);
	return MTM_SUCCESS;
}

MtmErrorCode addFirstAvailableOrder(EscapeSystem system, Order order, \
		SetElement room, SetElement escaper ) {
	int days_from_today = 0;
	while ( true ) {
		for( int hour = 0; hour < 24; hour++) {
			if ( isRoomAvailable(system, days_from_today, hour, room) && \
					isEscaperAvailable(system, days_from_today, hour, escaper) ) {
				setOrderHour(order, hour);
				Day day = returnDayFromToday(system, days_from_today);

				List orders = day->dayOrders;
				listInsertFirst(orders, order);
				return MTM_SUCCESS;
			}
		}
		days_from_today++;
	}
	return MTM_SUCCESS;
}

bool IsRoomOrdered(const EscapeSystem system, TechnionFaculty faculty,int id) {
	LIST_FOREACH(Day, dayVal, system->days) {
		LIST_FOREACH(Order, orderVal, dayVal->dayOrders) {
			if ( orderVal->faculty == faculty && orderVal->id == id ) {
				return true;
			}
		}
	}
	return false;
}

Day returnDayFromToday(const EscapeSystem system, int days_from_today) {
	if( system == NULL ) return NULL;
	if ( days_from_today == 0 ) return listGetFirst(system->days);
	Day day = listGetFirst(system->days);
	int last_day_number  = day->dayNumber;
	while ( day != NULL ) {
		last_day_number  = day->dayNumber;
		day = listGetNext(system->days);
	}

	while ( listGetSize(system->days) <= days_from_today ) {
		Day newDay = createDay(++last_day_number);
		if ( newDay == NULL ) {
			freeDay(newDay);
			return MTM_OUT_OF_MEMORY;
		}
		listInsertLast(system->days, newDay);
		freeDay(newDay);
	}

	day = listGetFirst(system->days);
	for(int i = 0; i < days_from_today; i++) {
		day = listGetNext(system->days);
	}

	return day;
}

MtmErrorCode removedOrdersOfEscaper(EscapeSystem system, const char* email ) {
	if( system == NULL || email == NULL ) return MTM_INVALID_PARAMETER;
	Day day = listGetFirst(system->days);
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
		day = listGetNext(system->days);
	}
	return MTM_SUCCESS;
}


List createFaculties(int number_of_faculties) {
	List faculties = listCreate(copyFaculty, freeFaculty);
	if ( faculties == NULL ) return NULL;

	Faculty new_faculty = malloc(sizeof(struct faculty_t));
	if ( new_faculty == NULL ) return NULL;
	for( int i = 0; i < number_of_faculties; i++) {
		new_faculty ->id = i;
		new_faculty ->income = 0;
		ListResult list_result = listInsertFirst(faculties, new_faculty );
		if ( list_result != LIST_SUCCESS ) return NULL;

	}
	free(new_faculty );
	return faculties;
}


Faculty findFacultyByNumber(List Faculties, TechnionFaculty faculty_number) {
	Faculty faculty = listGetFirst(Faculties);
	while ( faculty != NULL ) {

		if ( faculty->id == faculty_number ) {
			return faculty;
		}
		faculty = listGetNext(Faculties);
	}
	return NULL;
}


List returnListOfBestNFaculties(List faculties, int number) {
	if( faculties == NULL) return NULL;
	listSort(faculties, compareFacultyByIncomeAndId);
	List new_list = listCreate(copyFaculty, freeFaculty);
	ListElement faculty = listGetFirst( faculties );
	for(int i = 0; i < number; i++) {
		listInsertLast(new_list, faculty);
		faculty = listGetNext( faculties );
	}
	return new_list;
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


MtmErrorCode reportDay(FILE* output_channel, EscapeSystem system) {
	Day today = listGetFirst(system->days);
	List orders = today->dayOrders;
	mtmPrintDayHeader(output_channel, today->dayNumber, listGetSize(orders));

	Escaper escaper = NULL;
	Room room = NULL;
	listSort(orders , sortOrderByTimeFacultyId);
	Order order = listGetFirst(orders);
	while ( order != NULL ) {
		escaper = findEscaperByEmail( system, order->email );
		room = findRoom(system, order->faculty, order->id);
		mtmPrintOrder(output_channel, escaper->email, escaper->typeSkill, \
				escaper->faculty, room->email, room->faculty, room->id, \
				order->hour, room->difficulty, order->num_ppl, order->price);
		addIncomeToFaculty( findFacultyByNumber(system->faculties, \
				room->faculty),	order->price );
		order = listGetNext(orders);
	}
	mtmPrintDayFooter(output_channel, today->dayNumber);

	if ( listGetSize(system->days) == 1 ) {
		Day day = createDay(today->dayNumber+1);
		listInsertLast(system->days, day);
		freeDay(day);
	}
	listGetFirst(system->days);
	listRemoveCurrent(system->days);
	return MTM_SUCCESS;
}

MtmErrorCode reportBest(FILE* output_channel, EscapeSystem system) {
	Day today = listGetFirst(system->days);

	listSort( system->faculties, compareFacultyByIncomeAndId);
	mtmPrintFacultiesHeader(output_channel, NUMBER_OF_FACULTIES, \
			today->dayNumber, returnTotalFacultiesRevenue(system->faculties));

	List bestList = returnListOfBestNFaculties(system->faculties, \
			NUMBER_OF_BEST);
	Faculty faculty = listGetFirst(bestList);
	while ( faculty != NULL ) {
		mtmPrintFaculty(output_channel, faculty->id, faculty->income);
		faculty = listGetNext(bestList);
	}
	mtmPrintFacultiesFooter(output_channel);
	listDestroy(bestList);

	return MTM_SUCCESS;
}





