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

//TODO move to other place
MtmErrorCode createOrder(List days, Set users, Set rooms, const char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl);

//TODO move to other place
MtmErrorCode addOrder(List days, Set users, Set rooms, char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl);


MtmErrorCode addOrder2(List days, Order order, int daysFromToday);

//TODO move to other place
MtmErrorCode addOrderToADay(List orders, Set users, Set rooms, const char* email, TechnionFaculty faculty, int id, int hour, int num_ppl);

//TODO move to other place
MtmErrorCode addRecommendedOrder(List days, Set users, Set rooms, char* email, int num_ppl );

bool filterOrderByHour(const ListElement listElement, const ListFilterKey hour);

bool filterOrderByEscaper(const ListElement listElement, ListFilterKey email);

bool filterOrderByFaculty(const ListElement listElement, const ListFilterKey faculty);

bool filterOrderById(const ListElement listElement, const ListFilterKey id);

int compareOrderByHour(ListElement listElement1, ListElement listElement2);

bool checkIfRoomAvailable(List days, int daysFromToday, int hour, ListElement room);

bool checkIfEscaperAvailable(List days, int daysFromToday, int hour, SetElement user);

MtmErrorCode checkAvailability(List orders, int hour, char* email, TechnionFaculty faculty, int id);

//TODO move to other place
int calculatePriceOfOrder( Set users, Set rooms, const char* email, const SetElement room);

MtmErrorCode addFirstAvailableOrder(List days, Order order, SetElement room, SetElement user );

int getDay( const char* time );

int getHour( const char* time );


ListElement copyDay(ListElement day);

void freeDay(ListElement day);

int ordersForToday(List days);

MtmErrorCode addToday(List days);

ListElement createDay(int dayNumber);

List createDays();


//TODO remove to other place
void printAllDays(List days);

//TODO remove to other place
void printAllOrders(List orders);

void printOrder(ListElement order);


#endif /* ORDER_H_ */
