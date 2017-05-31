/*
 * order.h
 *
 *  Created on: May 28, 2017
 *      Author: master
 */

#ifndef ORDER_H_
#define ORDER_H_

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


MtmErrorCode add_order(char* email, char* faculty);



#endif /* ORDER_H_ */
