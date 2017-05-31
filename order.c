/*
 * order.c
 *
 *  Created on: May 28, 2017
 *      Author: master
 */


#include "order.h"

MtmErrorCode add_order(char* email, char* faculty) {
	return MTM_SUCCESS;
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
	newOrder->day = ((Order)order)->day;
	newOrder->hour = ((Order)order)->hour;
	return newOrder;
}


void freeOrder(ListElement order){
	if ( order == NULL ) return;
	free(((Order)order)->email);
	free((Order)order);
}
