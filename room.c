/*
 * room.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */


#include "room.h"


#define DISCONT 25 //Percents


int fromHour(const char* working_hrs);
int toHour(const char* working_hrs);
int charToInt(char c);



SetElement copyRoom(SetElement room) {
	if ( room == NULL ) return NULL;
	Room new_room = malloc(sizeof(struct room_t));
	if( new_room == NULL ) return NULL;
	new_room->email = malloc(sizeof(char) * (strlen(((Room)room)->email) + 1));
	if( new_room->email == NULL ) {
		free(new_room);
		return NULL;
	}
	strcpy(new_room->email, ((Room)room)->email);

	new_room->id = ((Room)room)->id;
	new_room->faculty = ((Room)room)->faculty;
	new_room->price = ((Room)room)->price;
	new_room->num_ppl = ((Room)room)->num_ppl;
	new_room->from_hrs = ((Room)room)->from_hrs;
	new_room->to_hrs = ((Room)room)->to_hrs;
	new_room->difficulty = ((Room)room)->difficulty;
	return new_room;
}

void freeRoom(SetElement room){
	if ( room == NULL ) return;
	free(((Room)room)->email);
	free((Room)room);
}

int compareRooms(const SetElement room1, const SetElement room2) {
	if ( room1 == NULL || room2 == NULL ) {
		return 0;
	}
	int faculty_compare = (((Room)room1)->faculty - ((Room)room2)->faculty);
	if ( faculty_compare == 0 ) {
		return ( ((Room)room1)->id - ((Room)room2)->id );
	} else {
		return faculty_compare;
	}
}

MtmErrorCode createRoom(Room new_room, const char* email, int id, int faculty, \
		int price, int num_ppl, int from, int to, int difficulty) {
	if ( email == NULL ) return MTM_INVALID_PARAMETER;
	new_room->email = malloc(sizeof(char) * (strlen(email)+1));
	if ( new_room->email == NULL) {
		free(new_room->email);
		return MTM_OUT_OF_MEMORY;
	}

	if (!idValidation(id)||!emailValidation(email)||!hoursValidation(from, to) \
			|| !skillLevelValidation(difficulty) || !priceValidation(price) || \
			!numberOfPeoplepriceValidation(num_ppl)) {
		free(new_room->email);
		return MTM_INVALID_PARAMETER;
	}

	strcpy(new_room->email, email);
	new_room->id = id;
	new_room->faculty = faculty;
	new_room->price = price;
	new_room->num_ppl = num_ppl;
	new_room->from_hrs = from;
	new_room->to_hrs = to;
	new_room->difficulty = difficulty;
	return MTM_SUCCESS;
}

int calculatePriceOfOrder(const Room room, TechnionFaculty escaper_faculty, \
		int num_ppl) {
	if( escaper_faculty == UNKNOWN ) return MTM_INVALID_PARAMETER;
	if ( room == NULL ) return MTM_ID_DOES_NOT_EXIST;

	if ( ((Room)room)->faculty == escaper_faculty ) \
			return ((((Room)room)->price * 75) / 100) * num_ppl;
	return room->price * num_ppl;
}



int filterByNumOfPplandDifficulty(const SetElement set_element, \
		SetKey num_ppl, SetKey skill_level ) {
	int delta_number_of_people = ((Room)set_element)->num_ppl-num_ppl;
	int delta_difficulty = ((Room)set_element)->difficulty - skill_level;
	return  delta_number_of_people*delta_number_of_people + \
			delta_difficulty*delta_difficulty;
}

int filterByNearFaculty(const SetElement set_element, SetKey faculty, \
		SetKey junk ) {
	return abs(((Room)set_element)->faculty - faculty);
}

int filterByNearId(const SetElement set_element, SetKey id, SetKey junk ) {
	return abs(((Room)set_element)->id - id);
}
