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


//#include "escaper.h"
#include "mtm_ex3.h"
#include "list.h"
#include "set.h"
//#include "room.h"

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

//TODO maybe remove or moved to other place
MtmErrorCode createOrder(List days, Set users, Set rooms, const char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl);

bool filterOrderByHour(const ListElement listElement, const ListFilterKey hour);

bool filterOrderByEscaper(const ListElement listElement, ListFilterKey email);

bool filterOrderByFaculty(const ListElement listElement, const ListFilterKey faculty);

bool filterOrderById(const ListElement listElement, const ListFilterKey id);

int compareOrderByHour(ListElement listElement1, ListElement listElement2);



MtmErrorCode checkAvailability(List orders, int hour, char* email, TechnionFaculty faculty, int id);


int getDay( const char* time );

int getHour( const char* time );




ListElement copyDay(ListElement day);

void freeDay(ListElement day);

int ordersForToday(List days);

MtmErrorCode addToday(List days);

ListElement createDay(int dayNumber);

List createDays();




//TODO remove
void printAllDays(List days);
//TODO remove
void printAllOrders(List orders);
//TODO remove
void printOrder(ListElement order);


#endif /* ORDER_H_ */
