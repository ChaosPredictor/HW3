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
#include "common.h"

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

/* copy escaper function
 * @param
 *	escaper - a new escaper object that same to the original *
 * @return
 *	escaper - copy of the escaper if success
 *	NULL - otherwise (memory leak)
 */
SetElement copyRoom(SetElement room);

/* free room function
 * @param
 * 	room - a room to free
 */
void freeRoom(SetElement room);

/* compare two rooms function
 * @param
 * 	room1 - first of the rooms to compare
 * 	room2 - second of the rooms to compare
 * @return
 * 	0 - room1 equal to room2 (email)
 * 	1 - room1 higher than room2 (email)
 * 	-1 - room2 higher than room1 (email)
 */
int compareRooms(const SetElement room1, const SetElement room2);

/* create a new room function
 * @param
 * 	room - a new room object that will be initialized
 * 	email - email of the room's company
 * 	id - id of the room
 * 	faculty - faculty of the room
 * 	price - price of the room
 * 	num_ppl - recommended number of people
 * 	from - from open hour
 * 	to - to open hour
 * 	difficulty - difficulty of the room
 * @return
 *	MTM_OUT_OF_MEMORY - out of memory
 *	MTM_INVALID_PARAMETER - if one of the parameters invalid
 *	MTM_SUCCESS - company created
 */
MtmErrorCode createRoom(Room newRoom, const char* email, int id, int faculty, int price, int num_ppl, int from, int to, int difficulty);

int calculatePriceOfOrder(const Room room, TechnionFaculty escaperFaculty, int num_ppl);




int filterByNumOfPplandDifficulty(const SetElement setElement, SetKey num_ppl, SetKey skill_level );

int filterByNearFaculty(const SetElement setElement, SetKey faculty, SetKey junk );

int filterByNearId(const SetElement setElement, SetKey id, SetKey junk );


#endif /* ROOM_H_ */
