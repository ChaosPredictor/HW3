/*
 * order.h
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <stdlib.h>
#include <string.h>
#include "mtm_ex3.h"
#include "list.h"

typedef struct order_t{
	char* email;
	TechnionFaculty faculty;
	int id;
	int price;
	int num_ppl;
	int day;
	int hour;
} *Order;

typedef struct day_t{
	List *dayOrders;
} *Day;



ListElement copyDay(ListElement day);

void freeDay(ListElement day);




ListElement copyOrder(ListElement order);

void freeOrder(ListElement order);

MtmErrorCode addOrder(List orders, char* email, TechnionFaculty faculty, int id, char* time, int num_ppl);


#endif /* ORDER_H_ */
