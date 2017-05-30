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
#include "mtm_escape.h"

//#include "visitor_room.h"
//TODO add related files

typedef struct room_t *Room;



MtmErrorCode addRoom(Set setRoom, const char* newEmail, TechnionFaculty faculty, int skill_level);

SetElement copyRoom(SetElement room);

void freeRoom(SetElement room);

int compareRoomes(SetElement room1, SetElement room2);



#endif /* ROOM_H_ */
