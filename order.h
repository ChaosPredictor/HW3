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
#include "list.h"
#include "common.h"



typedef struct order_t{
	char* email;
	TechnionFaculty faculty;
	int id;
	int price;
	int num_ppl;
	int hour;
} *Order;

typedef struct day_t{
	List day_orders;
	int day_number;
} *Day;



/* copy day function
 * @param
 *	day - a new day object that same to the original *
 * @return
 *	day - copy of the day if success
 *	NULL - otherwise (memory leak)
 */
ListElement copyDay(ListElement day);

/* free day function
 * @param
 * 	day - an day to free
 */
void freeDay(ListElement day);

/* create a new day function
 * @param
 * 	day_number - day number from the beginning
 * @return
 *	day - initialized day
 *	NULL - otherwise
 */
ListElement initDay(int day_number);


/* create a new list of days function
 * @return
 *	list - list of days
 *	NULL - otherwise (out of memory)
 */
List createDays();


/* copy order function
 * @param
 *	order - a new order object that same to the original *
 * @return
 *	order - copy of the order if success
 *	NULL - otherwise (memory leak)
 */
ListElement copyOrder(ListElement order);

/* free order function
 * @param
 * 	order - an day to free
 */
void freeOrder(ListElement order);

/* initialize a new order function
 * @param
 *	order - order to initialize
 *	email - email of the order escaper
 *	faculty - faculty of the room than ordered
 *	id - id of the room that ordered
 *	price - price of the room that ordered
 *	num_ppl - number of people of the order
 *	hour - order hour
 * @return
 *	MTM_OUT_OF_MEMORY - out of memory
 *	MTM_INVALID_PARAMETER - invalid parameter
 *	MTM_SUCCESS - initialization or the order succeeded
 */
MtmErrorCode initOrder(Order order, const char* email, \
		TechnionFaculty faculty, int id, int price, int num_ppl, int hour );

/* set order hour
 * @param
 *	order - order to initialize
 *	hour - order hour
 * @return
 *	MTM_INVALID_PARAMETER - invalid parameter (order == NULL)
 *	MTM_SUCCESS - initialization or the order succeeded
 */
MtmErrorCode setOrderHour(Order order, int hour);


/* filter order by order hour
 * @param
 *	listElement - order to check
 *	hour - order hour
 * @return
 * 	true - if the order is that same hour as hour
 * 	false - otherwise
 */
bool filterOrderByHour(const ListElement listElement, const ListFilterKey hour);

/* filter order by order email (escaoer)
 * @param
 *	listElement - order to check
 *	email - escaper email
 * @return
 * 	true - if the order is the same email as email
 * 	false - otherwise
 */
bool filterOrderByEscaper(const ListElement listElement, \
		const ListFilterKey email);

/* filter order by order room faculty
 * @param
 *	listElement - order to check
 *	faculty - room faculty
 * @return
 * 	true - if the order is the same faculty as faculty
 * 	false - otherwise
 */
bool filterOrderByFaculty(const ListElement listElement, \
		const ListFilterKey faculty);

/* filter order by order room id
 * @param
 *	listElement - order to check
 *	faculty - room id
 * @return
 * 	true - if the order is the same id as id
 * 	false - otherwise
 */
bool filterOrderById(const ListElement listElement, const ListFilterKey id);

/* compare two order function
 * @param
 * 	order1 - first of the order to compare
 * 	order2 - second of the order to compare
 * @return
 * 	0 - order1 equal to order2 (hour)
 * 	1 - order1 higher than order2 (hour)
 * 	-1 - order2 higher than order1 (hour)
 */
int compareOrderByTimeFacultyId(const ListElement listElement1, \
		const ListElement listElement2);





#endif /* ORDER_H_ */
