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
	newOrder->day = ((Order)order)->day;
	newOrder->hour = ((Order)order)->hour;
	return newOrder;
}


void freeOrder(ListElement order){
	if ( order == NULL ) return;
	free(((Order)order)->email);
	free((Order)order);
}


MtmErrorCode addOrder(List orders, char* email, TechnionFaculty faculty, int id, char* time, int num_ppl) {

	Order newOrder = malloc(sizeof(struct order_t));
	newOrder->email = malloc(sizeof(char) * 10);
	strcpy(newOrder->email, "dfsdf");

	listInsertFirst(orders, newOrder);
	free(newOrder->email);
	free(newOrder);

	/*
	if ( rooms == NULL || users == NULL ) return MTM_INVALID_PARAMETER;
	if ( email == NULL || !emailValidity(email) )  return MTM_INVALID_PARAMETER;

	TechnionFaculty faculty = findCompanyFacultyFromEmail(users, email);
	if ( faculty == UNKNOWN ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;


	//TODO check email exist
	//TODO check email not in the list
	//TODO faculty & id unic
	Room newRoom = malloc(sizeof(struct room_t));
	if ( newRoom == NULL) {
		return MTM_OUT_OF_MEMORY;
	}
	newRoom->email = malloc(sizeof(char) * (strlen(email)+1));
	if ( newRoom->email == NULL) {
		free(newRoom);
		return MTM_OUT_OF_MEMORY;
	}
	if ( id < 1 || price < 1 || price % 4 != 0 || num_ppl < 1) {
		free(newRoom->email);
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}

	int from =  fromHour(working_hrs);
	int to =  toHour(working_hrs);

	if ( from < 0 || from >= to || to > 23) {
		free(newRoom->email);
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}

	if ( difficulty < 1 || difficulty > 10 ) {
		free(newRoom->email);
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}

	strcpy(newRoom->email, email);
	newRoom->id = id;
	newRoom->faculty = faculty;
	newRoom->price = price;
	newRoom->num_ppl = num_ppl;
	newRoom->from_hrs = from;
	newRoom->to_hrs = to;
	newRoom->difficulty = difficulty;
	//printf("faculty: %d id: %d\n", faculty, id);
	if( setIsIn(rooms, newRoom) ) {
		free(newRoom->email);
		free(newRoom);
		return MTM_ID_ALREADY_EXIST;
	}

	setAdd(rooms, newRoom);
	free(newRoom->email);
	free(newRoom);*/
	return MTM_SUCCESS;
}




ListElement copyDay(ListElement day) {
	if ( day == NULL ) return NULL;
	//TODO maybe assert
	Day newDay = malloc(sizeof(struct day_t));
	if( newDay == NULL ) return NULL;
	List newList = listCreate(copyOrder ,freeOrder);
	List list = *((Day)day)->dayOrders;
	newList = listCopy(list);
	newDay->dayOrders = &newList;
	return newDay;
}


