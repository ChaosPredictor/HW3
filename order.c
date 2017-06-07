/*
 * order.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */


#include "order.h"


ListElement copyOrder(ListElement order) {
	if ( order == NULL ) return NULL;
	//TODO maybe assert
	Order newOrder = malloc(sizeof(struct order_t));
	if( newOrder == NULL ) return NULL;
	newOrder->email = malloc(sizeof(char) * (strlen(((Order)order)->email) + 1));
	if( newOrder->email == NULL ) {
		free( newOrder );
		return NULL;
	}
	strcpy(newOrder->email, ((Order)order)->email);
	newOrder->faculty = ((Order)order)->faculty;
	newOrder->id = ((Order)order)->id;
	newOrder->price = ((Order)order)->price;
	newOrder->num_ppl = ((Order)order)->num_ppl;
	newOrder->hour = ((Order)order)->hour;
	return newOrder;
}


void freeOrder(ListElement order) {
	if ( order == NULL ) return;
	free(((Order)order)->email);
	free((Order)order);
}


MtmErrorCode addOrderToADay(List orders, Set users, Set rooms, const char* email, TechnionFaculty faculty, int id, int hour, int num_ppl) {
	//TODO escaper email should be checked before this function
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

	if( users==NULL || rooms==NULL || orders == NULL ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_INVALID_PARAMETER;
	}

	if ( returnEscaperFaculty( findEscaperByEmail(users, email) ) == UNKNOWN ) {
	//if ( findEscaperFacultyFromEmail(users, email) == UNKNOWN ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}
/*
	Room room = findRoom(rooms, faculty, id);
	if ( room == NULL ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_ID_DOES_NOT_EXIST;
	}
	if( hour < room->from_hrs || hour >= room->to_hrs ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_ROOM_NOT_AVAILABLE;
	}
*/
	newOrder->faculty = faculty;
	newOrder->id = id;
	newOrder->price = 10;
			//calculatePriceOfOrder( users, rooms, email, room);
	newOrder->hour = hour;
	newOrder->num_ppl = num_ppl;

	listInsertFirst(orders, newOrder);
	free(newOrder->email);
	free(newOrder);

	//TODO check that the room (faculty&id) available in the hour;
	//TODO check that the escaper available in the hour;
	return MTM_SUCCESS;
}

//TODO should move to system
/*
MtmErrorCode addOrder(List days, Set users, Set rooms, char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl) {
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

	if ( findEscaperFacultyFromEmail(users, email) == UNKNOWN ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}
	User escaper = findUserFromEmail( users, email );

	int hour = getHour( time );
	int daysFromToday = getDay( time );

	Room room = findRoom(rooms, faculty, id);
	if ( room == NULL ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_ID_DOES_NOT_EXIST;
	}

	newOrder->faculty = faculty;
	newOrder->id = id;
	newOrder->price = calculatePriceOfOrder( users, rooms, email, room) * num_ppl;
	newOrder->hour = hour;
	newOrder->num_ppl = num_ppl;


	//
	if ( !checkIfRoomAvailable(days, daysFromToday, hour, room) ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_ROOM_NOT_AVAILABLE;
	}

	if ( !checkIfEscaperAvailable(days, daysFromToday, hour, escaper) ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_IN_ROOM;
	}*/
	/*
	if ( checkIfRoomAvailable(days, daysFromToday, hour, room) && checkIfEscaperAvailable(days, daysFromToday, hour, escaper) ) {

	}

	addOrder2(days, newOrder, daysFromToday);
	free(newOrder->email);
	free(newOrder);
	return MTM_SUCCESS;
}*/
	//TODO check faculty validity



	/*
	assert( days != NULL );

	int hour = getHour( time );
	int daysFromToday = getDay( time );

	Day day = listGetFirst(days);

	int dayNumber = day->dayNumber;
	while ( day != NULL && day->dayNumber < dayNumber + daysFromToday ) {
		day = listGetNext(days);
	}
	if ( day == NULL ) {
		Day newDay = createDay(dayNumber + daysFromToday);
		List orders = newDay->dayOrders;
		MtmErrorCode result = addOrderToADay(orders, users, rooms, email, faculty, id,  hour, num_ppl);
		if ( result != MTM_SUCCESS) {
			freeDay(newDay);
			return result;
		}
		//TODO check return;
		listInsertLast(days, newDay);
		freeDay(newDay);
	} else if ( day->dayNumber ==  dayNumber + daysFromToday ) {
			List orders = day->dayOrders;

			MtmErrorCode result = checkAvailability(orders, hour, email, faculty, id);
			if ( result != MTM_SUCCESS) return result;
			result = addOrderToADay(orders, users, rooms, email, faculty, id,  hour, num_ppl);
			if ( result != MTM_SUCCESS) return result;
	} else {
		Day newDay = createDay(dayNumber + daysFromToday);
		List orders = newDay->dayOrders;
		MtmErrorCode result = addOrderToADay(orders, users, rooms, email, faculty, id,  hour, num_ppl);
		if ( result != MTM_SUCCESS) {
			freeDay(newDay);
			return result;
		}
		listInsertBeforeCurrent(days, newDay);
		freeDay(newDay);
	}
	return MTM_SUCCESS;
}*/
/*
MtmErrorCode addRecommendedOrder(List days, Set users, Set rooms, char* email, int num_ppl ) {
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

	if ( findEscaperFacultyFromEmail(users, email) == UNKNOWN ) {
		free(newOrder->email);
		free(newOrder);
		return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	}
	User escaper = findUserFromEmail( users, email );
	newOrder->num_ppl = num_ppl;

	//printf("\n number1: %d\n", setGetSize(rooms));
	MtmErrorCode result = MTM_SUCCESS;
	Set recommendedRooms = setCopy(rooms);

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

		result = addFirstAvailableOrder(days, newOrder, room, escaper);
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
*/


MtmErrorCode addFirstAvailableOrder(List days, Order order, SetElement room, SetElement escaper ) {
	//printRoom(room);
	//return MTM_SUCCESS;

	bool done = false;
	int daysFromToday = 0;

	while ( !done ) {
		for( int hour = 0; hour < 24; hour++) {
			if ( checkIfRoomAvailable(days, daysFromToday, hour, room) && checkIfEscaperAvailable(days, daysFromToday, hour, escaper) ) {
				order->hour = hour;
				MtmErrorCode result = addOrder2(days, order, daysFromToday);
				//TODO maybe should be checked
				return result;
			}
		}
		daysFromToday++;
	}
	return MTM_SUCCESS;
}


MtmErrorCode addOrder2(List days, Order order, int daysFromToday) {
	Day day = listGetFirst(days);
	bool endOfList = false;
	int i = 0;
	while ( !endOfList && i < daysFromToday ) {
		day = listGetNext(days);
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
		listInsertLast(days, newDay);
		freeDay(newDay);
		i++;
	}
	if ( endOfList ) {
		day = listGetFirst(days);
		for (int i = 0; i < daysFromToday; i++ ) {
			day = listGetNext(days);
		}
	}
	List orders = day->dayOrders;
	listInsertFirst(orders, order);
	return MTM_SUCCESS;
}

//TODO should move from here
bool checkIfEscaperAvailable(List days, int daysFromToday, int hour, SetElement escaper) {
	Day day = listGetFirst(days);
	for(int i = 0; i < daysFromToday; i++ ) {
		day = listGetNext(days);
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


bool checkIfRoomAvailable(List days, int daysFromToday, int hour, ListElement room) {
	if ( ((Room)room)->from_hrs > hour || ((Room)room)->to_hrs < hour ) return false;

	Day day = listGetFirst(days);

	for(int i = 0; i < daysFromToday; i++ ) {
		day = listGetNext(days);
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


MtmErrorCode checkAvailability(List orders, int hour, char* email, TechnionFaculty faculty, int id) {
	List filteredOrders = listFilter(orders, filterOrderByHour, &hour);
	if ( listGetSize(filteredOrders) > 0 ) {
		List filteredOrdersEscaper = listFilter(filteredOrders, filterOrderByEscaper, email);
		if ( listGetSize(filteredOrdersEscaper) > 0 ) {

			listDestroy(filteredOrders);
			listDestroy(filteredOrdersEscaper);
			return MTM_CLIENT_IN_ROOM;
		}
		listDestroy(filteredOrdersEscaper);
		List filteredOrdersFaculty = listFilter(filteredOrders, filterOrderByFaculty, &faculty);
		if ( listGetSize(filteredOrdersFaculty) > 0 ) {
			List filteredOrdersId = listFilter(filteredOrders, filterOrderById, &id);
			if ( listGetSize(filteredOrdersId) > 0 ) {
				listDestroy(filteredOrdersId);
				listDestroy(filteredOrdersFaculty);
				listDestroy(filteredOrders);
				return MTM_ROOM_NOT_AVAILABLE;
			}
			listDestroy(filteredOrdersId);
		}
		listDestroy(filteredOrdersFaculty);
	}
	listDestroy(filteredOrders);
	return MTM_SUCCESS;
}
/*
int calculatePriceOfOrder( Set users, Set rooms, const char* email, const SetElement room) {
	TechnionFaculty escaperFaculty = returnEscaperFaculty( findEscaperByEmail(users, email));
	if( escaperFaculty == UNKNOWN ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;

	if ( room == NULL ) return MTM_ID_DOES_NOT_EXIST;
	int price = ((Room)room)->price;
	if ( escaperFaculty == ((Room)room)->faculty ) {
		price *= (100 - DISCONT);
		price /= 100;
	}
	return price;
}*/

int getHour( const char* time ) {
	char *temp = malloc(sizeof(char) * (strlen(time) + 1));
	strcpy(temp,time);
	atoi( strtok(temp, "-") );
	int hour = atoi( strtok(NULL, "-") );
	free( temp );
	return hour;
}

int getDay( const char* time ) {
	char *temp = malloc(sizeof(char) * (strlen(time) + 1));
	strcpy(temp,time);
	int daysFromToday = atoi( strtok(temp, "-") );
	free( temp );
	return daysFromToday;
}


//TODO maybe should be deleted
int orderForToday (List days) {
	if( days==NULL ) return MTM_INVALID_PARAMETER;

	return 0;
}

//TODO maybe should be deleted
void printAllDays(List days) {
	printf("\nA New Print\n");
	Day day = listGetFirst(days);
	while ( day != NULL ) {
		printf(" Day Number: %d\n", day->dayNumber);
		printAllOrders(day->dayOrders);
		day = listGetNext(days);
	}
}

void printAllOrders(List orders) {
	Order order = listGetFirst(orders);
	while ( order != NULL ) {
		printf("  A New Order\n");
		printf("	Order email: %s\n", order->email);
		printf("	Order faculty: %d\n", order->faculty);
		printf("	Order id: %d\n", order->id);
		printf("	Order hour: %d\n", order->hour);
		printf("	Order price: %d\n", order->price);
		order = listGetNext(orders);
	}
}


void printOrder(ListElement order) {
	printf("  A New Order\n");
	printf("	Order email: %s\n", ((Order)order)->email);
	printf("	Order faculty: %d\n", ((Order)order)->faculty);
	printf("	Order id: %d\n", ((Order)order)->id);
	printf("	Order hour: %d\n", ((Order)order)->hour);
	printf("	Order price: %d\n", ((Order)order)->price);
}

ListElement copyDay(ListElement day) {
	if ( day == NULL ) return NULL;
	//TODO maybe assert
	Day newDay = malloc(sizeof(struct day_t));
	if( newDay == NULL ) return NULL;
	List newList;
	if (((Day)day)->dayOrders != NULL ) {
		List list = ((Day)day)->dayOrders;
		newList = listCopy(list);
	} else {
		newList = listCreate(copyOrder ,freeOrder);
	}
	newDay->dayNumber = ((Day)day)->dayNumber;
	newDay->dayOrders = newList;
	return newDay;
}

void freeDay(ListElement day) {
	if ( day == NULL ) return;
	listDestroy((((Day)day)->dayOrders));
	free((Day)day);
}

ListElement createDay(int dayNumber) {
	Day newDay = malloc(sizeof(struct day_t));
	if( newDay == NULL ) return NULL;
	newDay->dayNumber = dayNumber;
	newDay->dayOrders = listCreate(copyOrder ,freeOrder);
	return newDay;
}

List createDays() {
	List days = listCreate(copyDay, freeDay);
	//List templist = listCreate(copyDay, freeDay);
	//printf("address1 %p\n", (void*)templist);
	//days = &templist;
	//printf("address2 %p\n", (void*)days);

	if ( days == NULL ) return NULL;
	Day newDay = malloc(sizeof(struct day_t));
	if ( newDay == NULL ) {
		listDestroy(days);
		return NULL;
	}
	newDay->dayOrders = NULL;
	newDay->dayNumber = 0;
	listInsertFirst(days, newDay);
	free(newDay);
	return days;
}


MtmErrorCode addToday(List days) {
	if ( days == NULL ) return MTM_INVALID_PARAMETER;
	Day newDay = malloc(sizeof(struct day_t));
	newDay->dayOrders = NULL;
	newDay->dayNumber = 0;
	listInsertFirst(days, newDay);
	printf("\nnumber of days: %d\n", listGetSize(days));
	return MTM_SUCCESS;
}

bool filterOrderByHour(const ListElement listElement, const ListFilterKey hour) {
	return ((((Order)listElement)->hour) == *(int*)hour);
}

bool filterOrderByEscaper(const ListElement listElement, ListFilterKey email) {
	return (strcmp((((Order)listElement)->email), (char*)email) == 0);
}

bool filterOrderByFaculty(const ListElement listElement, const ListFilterKey faculty) {
	return ((((Order)listElement)->faculty) == *(int*)faculty);
}

bool filterOrderById(const ListElement listElement, const ListFilterKey id) {
	return ((((Order)listElement)->id) == *(int*)id);
}

//TODO maybe wrong
int compareOrderByHour(ListElement listElement1, ListElement listElement2) {
	return ((((Order)listElement2)->hour) == (((Order)listElement1)->hour));
}





