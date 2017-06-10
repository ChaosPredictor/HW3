/*
 * order.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */


#include "order.h"




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
	Day newDay = createDay(0);

	listInsertFirst(days, newDay);
	freeDay(newDay);
	return days;
}

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

MtmErrorCode createOrder(Order order, const char* email, TechnionFaculty faculty, int id, int price, int num_ppl, int hour ) {
	//printf("\n\nfaculty: %d\n\n", faculty);
	if( order == NULL || !emailValidity(email)  || !facultyValidity(faculty)) return MTM_INVALID_PARAMETER;


	order->email = malloc(sizeof(char) * (strlen(email)+1));


	if( order->email == NULL ) return MTM_OUT_OF_MEMORY;
	strcpy( order->email, email);

	order->faculty = faculty;
	order->id = id;
	order->price = price;
	order->num_ppl = num_ppl;
	order->hour = hour;
	return MTM_SUCCESS;
}


MtmErrorCode setOrderHour(Order order, int hour) {
	order->hour = hour;
	return MTM_SUCCESS;
}



bool filterOrderByHour(const ListElement listElement, const ListFilterKey hour) {
	return ((((Order)listElement)->hour) == *(int*)hour);
}

bool filterOrderByEscaper(const ListElement listElement, const ListFilterKey email) {
	return (strcmp((((Order)listElement)->email), (char*)email) == 0);
}

bool filterOrderByFaculty(const ListElement listElement, const ListFilterKey faculty) {
	return ((((Order)listElement)->faculty) == *(int*)faculty);
}

bool filterOrderById(const ListElement listElement, const ListFilterKey id) {
	return ((((Order)listElement)->id) == *(int*)id);
}

int sortOrderByTimeFacultyId(const ListElement listElement1, const ListElement listElement2) {
	Order order1 = (Order)listElement1;
	Order order2 = (Order)listElement2;
	if ( (order1->hour) > (order2->hour) ) {
		return 1;
	} else if ( (order1->hour) < (order2->hour) ) {
		return -1;
	} else if ( (order1->faculty) > (order2->faculty) ) {
		return 1;
	} else if ( (order1->faculty) < (order2->faculty) ) {
		return -1;
	} else if ( (order1->id) > (order2->id) ) {
		return 1;
	} else if ( (order1->id) < (order2->id) ) {
		return -1;
	}
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




