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
	//TODO check that the room (facultyid) available in the hour;
	return MTM_SUCCESS;
}



MtmErrorCode addOrder(List days, Set users, Set rooms, const char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl) {
	if(days==NULL || users==NULL || rooms==NULL) return MTM_INVALID_PARAMETER;
	if( !emailValidity(email) ) return MTM_INVALID_PARAMETER;
	TechnionFaculty escaperFaculty = findEscaperFacultyFromEmail( users, email );
	if( escaperFaculty == UNKNOWN ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;




	Room room = findRoom(rooms, faculty, id);
	if ( room == NULL ) return MTM_ID_DOES_NOT_EXIST;

	int price = room->price;
	if ( escaperFaculty == faculty ) {
		price *= (100 - DISCONT)/100;
	}
	char *temp = malloc(sizeof(char) * (strlen(time) + 1));
	strcpy(temp,time);
	int daysFromToday = atoi( strtok(temp, "-") );
	int hour = atoi( strtok(NULL, "-") );
	free( temp );

	Day day = listGetFirst(days);
	if ( day != NULL && daysFromToday != 0 ) {
		int dayNumber = day->day;
		//printf("\nday today: %d \n", day->day);
		//printf("\nday today: %d || day Number: %d || days from today: %d\n", day->day, dayNumber, daysFromToday);
		while ( day != NULL && day->day < dayNumber + daysFromToday ) {
			day = listGetNext(days);
		}
	} else {
		printf("\ntoday\n");
	}

	Day firstDay = listGetFirst(days);
	List orders = firstDay->dayOrders;

	addOrderToADay(orders, email, faculty, id, price, hour, num_ppl);

	//TODO escaper email should be checked before this function

/*
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
	newOrder->hour = hour;
	newOrder->num_ppl = num_ppl;

	listInsertFirst(orders, newOrder);
	free(newOrder->email);
	free(newOrder);*/
	//TODO check that the room (facultyid) available in the hour;
	return MTM_SUCCESS;
}

//TODO maybe should be deleted
int orderForToday (List days) {
	if( days==NULL ) return MTM_INVALID_PARAMETER;

	return 0;
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
	newDay->day = ((Day)day)->day;
	newDay->dayOrders = newList;
	return newDay;
}

void freeDay(ListElement day) {
	if ( day == NULL ) return;
	listDestroy((((Day)day)->dayOrders));
	free((Day)day);
}


List daysCreate() {
	List days = listCreate(copyDay, freeDay);
	if ( days == NULL ) return NULL;
	Day newDay = malloc(sizeof(struct day_t));
	if ( newDay == NULL ) {
		listDestroy(days);
		return NULL;
	}
	newDay->dayOrders = NULL;
	newDay->day = 8;
	listInsertFirst(days, newDay);
	free(newDay);
	return days;
}


MtmErrorCode addToday(List days) {
	if ( days == NULL ) return MTM_INVALID_PARAMETER;
	Day newDay = malloc(sizeof(struct day_t));
	newDay->dayOrders = NULL;
	newDay->day = 0;
	listInsertFirst(days, newDay);
	printf("\nnumber of days: %d\n", listGetSize(days));
	return MTM_SUCCESS;
}
