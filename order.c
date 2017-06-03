/*
 * order.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */


#include "order.h"

#define DISCONT 25 //Percents

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


MtmErrorCode addOrderToADay(List orders, const char* email, TechnionFaculty faculty, int id, int price, int hour, int num_ppl) {
	//TODO escaper email should be checked before this function

	if ( orders == NULL || email == NULL ) return MTM_INVALID_PARAMETER;


	Order newOrder = malloc(sizeof(struct order_t));
	if ( newOrder == NULL) {
		return MTM_OUT_OF_MEMORY;
	}
	newOrder->email = malloc(sizeof(char) * (strlen(email) + 1));
	if ( newOrder->email == NULL) {
		free(newOrder);
		return MTM_OUT_OF_MEMORY;
	}
	strcpy(newOrder->email, email);
	newOrder->faculty = faculty;
	newOrder->id = id;
	newOrder->price = price;
	newOrder->hour = hour;
	newOrder->num_ppl = num_ppl;

	listInsertFirst(orders, newOrder);
	free(newOrder->email);
	free(newOrder);

	//TODO check that the room (faculty&id) available in the hour;
	//TODO check that the escaper available in the hour;
	return MTM_SUCCESS;
}



MtmErrorCode addOrder(List days, Set users, Set rooms, char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl) {
	if(days==NULL || users==NULL || rooms==NULL) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	TechnionFaculty escaperFaculty = findEscaperFacultyFromEmail( users, email );
	if( escaperFaculty == UNKNOWN ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;




	Room room = findRoom(rooms, faculty, id);
	if ( room == NULL ) return MTM_ID_DOES_NOT_EXIST;

	int price = room->price;
	//printf("\nroom price: %d\n", price);

	if ( escaperFaculty == faculty ) {
		price *= (100 - DISCONT);
		price /= 100;
	}
	char *temp = malloc(sizeof(char) * (strlen(time) + 1));
	strcpy(temp,time);
	int daysFromToday = atoi( strtok(temp, "-") );
	int hour = atoi( strtok(NULL, "-") );
	free( temp );

	if( hour < room->from_hrs || hour >= room->to_hrs ) return MTM_ROOM_NOT_AVAILABLE;

	Day day = listGetFirst(days);
	List orders = NULL;


	int dayNumber = day->dayNumber;
	//printf("\nday today: %d \n", day->day);
	//printf("\nday today: %d || day Number: %d || days from today: %d\n", day->day, dayNumber, daysFromToday);
	while ( day != NULL && day->dayNumber < dayNumber + daysFromToday ) {
		day = listGetNext(days);
		//printf("\nrun\n");
	}
	if ( day == NULL ) {
		Day newDay = createDay(dayNumber + daysFromToday);
		orders = newDay->dayOrders;


		addOrderToADay(orders, email, faculty, id, price, hour, num_ppl);
		listInsertLast(days, newDay);
		freeDay(newDay);
		//TODO check return;
		//printf("\nend of list\n");
	} else {
		if ( day->dayNumber ==  dayNumber + daysFromToday ) {
			orders = day->dayOrders;
				//printf("\ntoday list size1 %d\n", listGetSize(orders));
				List filteredOrders = listFilter(orders, filterOrderByHour, &hour);
			//printf("\ntoday list size2 %d\n", listGetSize(filteredOrders));
				if ( listGetSize(filteredOrders) > 0 ) {
				List filteredOrdersEscaper = listFilter(filteredOrders, filterOrderByEscaper, email);
				//printf("\ntoday list size3 %d\n", listGetSize(filteredOrdersEscaper));
					if ( listGetSize(filteredOrdersEscaper) > 0 ) {
						listDestroy(filteredOrders);
						listDestroy(filteredOrdersEscaper);
						return MTM_CLIENT_IN_ROOM;
					}
					listDestroy(filteredOrdersEscaper);

				}
				listDestroy(filteredOrders);


			addOrderToADay(orders, email, faculty, id, price, hour, num_ppl);
				//printf("\nday found\n");

		} else {
			//printf("\nday does not found\n");
			Day newDay = createDay(dayNumber + daysFromToday);
			orders = newDay->dayOrders;
			addOrderToADay(orders, email, faculty, id, price, hour, num_ppl);
			listInsertBeforeCurrent(days, newDay);
			freeDay(newDay);
		}
	}



	//TODO escaper email should be checked before this function

	//TODO check that the room (facultyid) available in the hour;
	return MTM_SUCCESS;
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
