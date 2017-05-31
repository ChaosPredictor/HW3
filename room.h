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
#include "set.h"
#include "order.h"
#include "mtm_escape.h"
#include "user.h"


//#include "visitor_room.h"
//TODO add related files

typedef struct room_t{
	char* email;
	int id;
	TechnionFaculty faculty;
	int price;
	int num_ppl;
	int from_hrs, to_hrs;
	int difficulty;
} *Room;



MtmErrorCode addRoom(Set rooms, Set companies, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty);

MtmErrorCode removeRoom(Set setRoom, TechnionFaculty faculty, int id);

SetElement copyRoom(SetElement room);

void freeRoom(SetElement room);

int compareRooms(SetElement room1, SetElement room2);



#endif /* ROOM_H_ */
