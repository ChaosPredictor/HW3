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

ListElement createDay(int dayNumber);

List createDays();



ListElement copyOrder(ListElement order);

void freeOrder(ListElement order);



bool filterOrderByHour(const ListElement listElement, const ListFilterKey hour);

bool filterOrderByEscaper(const ListElement listElement, const ListFilterKey email);

bool filterOrderByFaculty(const ListElement listElement, const ListFilterKey faculty);

bool filterOrderById(const ListElement listElement, const ListFilterKey id);






//TODO remove
void printAllDays(List days);
//TODO remove
void printAllOrders(List orders);
//TODO remove
void printOrder(ListElement order);


#endif /* ORDER_H_ */
