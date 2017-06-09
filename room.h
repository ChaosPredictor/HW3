/*
 * room.h
 *
 *  Created on: May 30, 2017
 *      Author: master
 */

#ifndef ROOM_H_
#define ROOM_H_



#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "set.h"
#include "mtm_ex3.h"

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


SetElement copyRoom(SetElement room);

void freeRoom(SetElement room);

int compareRooms(const SetElement room1, const SetElement room2);


MtmErrorCode createRoom(Room newRoom, const char* email, int id, int faculty, int price, int num_ppl, const char* working_hrs, int difficulty);

int calculatePriceOfOrder(const Room room, TechnionFaculty escaperFaculty, int num_ppl);

int returnRoomPrice(const Room room);



int filterByNumOfPplandDifficulty(const SetElement setElement, SetKey num_ppl, SetKey skill_level );

int filterByNearFaculty(const SetElement setElement, SetKey faculty, SetKey junk );

int filterByNearId(const SetElement setElement, SetKey id, SetKey junk );



//TODO should be removed;
void printRoom(const SetElement setElement);

#endif /* ROOM_H_ */
