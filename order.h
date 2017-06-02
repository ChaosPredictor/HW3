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
#include "user.h"
#include "room.h"

typedef struct order_t{
	char* email;
	TechnionFaculty faculty;
	int id;
	int price;
	int num_ppl;
	int hour;
} *Order;

typedef struct day_t{
	List dayOrders;
	int dayNumber;
} *Day;



ListElement copyDay(ListElement day);

void freeDay(ListElement day);




ListElement copyOrder(ListElement order);

void freeOrder(ListElement order);

MtmErrorCode createOrder(List days, Set users, Set rooms, const char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl);

MtmErrorCode addOrder(List days, Set users, Set rooms, const char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl);

MtmErrorCode addOrderToADay(List orders, const char* email, TechnionFaculty faculty, int id, int price, int hour, int num_ppl);



ListElement copyDay(ListElement day);

void freeDay(ListElement day);

int ordersForToday(List days);

MtmErrorCode addToday(List days);

ListElement createDay(int dayNumber);

List createDays();

#endif /* ORDER_H_ */
