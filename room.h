/*
 * room.h
 *
 *  Created on: May 30, 2017
 *      Author: master
 */

#ifndef ROOM_H_
#define ROOM_H_



#include <assert.h>
#include <string.h>

#include "order.h"
#include "company.h"
#include "mtm_escape.h"


//#include "visitor_room.h"
//TODO add related files

typedef struct room_t *Room;



MtmErrorCode addRoom(Set rooms, Set companies, char* email, int id, int price, int num_ppl, int from_hrs, int to_hrs, int difficulty);

SetElement copyRoom(SetElement room);

void freeRoom(SetElement room);

int compareRoomes(SetElement room1, SetElement room2);



#endif /* ROOM_H_ */
