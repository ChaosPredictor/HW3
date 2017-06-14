/*
 * order.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */


#include "order.h"




ListElement copyDay(ListElement day) {
	if ( day == NULL ) return NULL;
	Day new_day = malloc(sizeof(struct day_t));
	if( new_day == NULL ) return NULL;
	List newList;
	if (((Day)day)->dayOrders != NULL ) {
		List list = ((Day)day)->dayOrders;
		newList = listCopy(list);
	} else {
		newList = listCreate(copyOrder ,freeOrder);
	}
	new_day->dayNumber = ((Day)day)->dayNumber;
	new_day->dayOrders = newList;
	return new_day;
}

void freeDay(ListElement day) {
	if ( day == NULL ) return;
	listDestroy((((Day)day)->dayOrders));
	free((Day)day);
}

ListElement createDay(int dayNumber) {
	Day new_day = malloc(sizeof(struct day_t));
	if( new_day == NULL ) return NULL;
	new_day->dayNumber = dayNumber;
	new_day->dayOrders = listCreate(copyOrder ,freeOrder);
	return new_day;
}



List createDays() {
	List days = listCreate(copyDay, freeDay);
	if ( days == NULL ) return NULL;
	Day new_day = createDay(0);

	listInsertFirst(days, new_day);
	freeDay(new_day);
	return days;
}

ListElement copyOrder(ListElement order) {
	if ( order == NULL ) return NULL;
	Order new_order = malloc(sizeof(struct order_t));
	if( new_order == NULL ) return NULL;
	new_order->email = malloc(sizeof(char)*(strlen(((Order)order)->email) + 1));
	if( new_order->email == NULL ) {
		free( new_order );
		return NULL;
	}
	strcpy(new_order->email, ((Order)order)->email);
	new_order->faculty = ((Order)order)->faculty;
	new_order->id = ((Order)order)->id;
	new_order->price = ((Order)order)->price;
	new_order->num_ppl = ((Order)order)->num_ppl;
	new_order->hour = ((Order)order)->hour;
	return new_order;
}

void freeOrder(ListElement order) {
	if ( order == NULL ) return;
	free(((Order)order)->email);
	free((Order)order);
}

MtmErrorCode createOrder(Order order, const char* email, \
		TechnionFaculty faculty, int id, int price, int num_ppl, int hour ) {
	if ( email != NULL && order!=NULL ) {
		order->email = malloc(sizeof(char) * (strlen(email)+1));
		if ( order->email == NULL ) return MTM_OUT_OF_MEMORY;
	} else {
		return MTM_INVALID_PARAMETER;
	}

	if( !emailValidation(email) || !facultyValidation(faculty) || \
			!idValidation(id) || !numberOfPeoplepriceValidation(num_ppl) || \
			!hourValidation (hour)){
		free(order->email);
		return MTM_INVALID_PARAMETER;
	}

	strcpy( order->email, email);

	order->faculty = faculty;
	order->id = id;
	order->price = price;
	order->num_ppl = num_ppl;
	order->hour = hour;
	return MTM_SUCCESS;
}


MtmErrorCode setOrderHour(Order order, int hour) {
	if( !hourValidation (hour) ){
		return MTM_INVALID_PARAMETER;
	}
	order->hour = hour;
	return MTM_SUCCESS;
}



bool filterOrderByHour(const ListElement list_element,const ListFilterKey hour){
	return ((((Order)list_element)->hour) == *(int*)hour);
}

bool filterOrderByEscaper(const ListElement list_element, \
		const ListFilterKey email) {
	return (strcmp((((Order)list_element)->email), (char*)email) == 0);
}

bool filterOrderByFaculty(const ListElement list_element, \
		const ListFilterKey faculty) {
	return ((((Order)list_element)->faculty) == *(int*)faculty);
}

bool filterOrderById(const ListElement list_element, const ListFilterKey id) {
	return ((((Order)list_element)->id) == *(int*)id);
}

int sortOrderByTimeFacultyId(const ListElement list_element1, \
		const ListElement list_element2) {
	Order order1 = (Order)list_element1;
	Order order2 = (Order)list_element2;
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




