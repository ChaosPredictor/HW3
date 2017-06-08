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



//TODO should move from here



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





