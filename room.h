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
#include <assert.h>
#include <math.h>
#include "set.h"
#include "order.h"
#include "system.h"
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

typedef int SetKey;


typedef int(*RecommendSetElement)(SetElement, SetKey, SetKey);


//TODO should move to system;
//TODO working hours should be const
MtmErrorCode addRoom(Set rooms, Set companies, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty);

MtmErrorCode removeRoom(Set setRoom, TechnionFaculty faculty, int id);

SetElement copyRoom(SetElement room);

void freeRoom(SetElement room);

int compareRooms(SetElement room1, SetElement room2);

int getRoomPrice(const Set rooms, TechnionFaculty faculty, int id);

SetElement findRoom(const Set rooms, TechnionFaculty faculty, int id);

int getRoomPrice(const Set rooms, TechnionFaculty faculty, int id);

Set filterRoomSet(Set rooms, RecommendSetElement recommendSetElement, SetKey num_ppl, SetKey skill_level );

int recommendByNumOfPplandDifficulty(const SetElement setElement, SetKey num_ppl, SetKey skill_level );

int recommendByNearFaculty(const SetElement setElement, SetKey faculty, SetKey junk );

int recommendByNearId(const SetElement setElement, SetKey id, SetKey junk );
//TODO should be removed;
void printRoom(const SetElement setElement);

#endif /* ROOM_H_ */
