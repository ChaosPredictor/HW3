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
	//TODO maybe assert
	Room newRoom = malloc(sizeof(struct room_t));
	if( newRoom == NULL ) return NULL;
	newRoom->email = malloc(sizeof(char) * (strlen(((Room)room)->email) + 1));
	if( newRoom->email == NULL ) {
		free(newRoom);
		return NULL;
	}
	strcpy(newRoom->email, ((Room)room)->email);

	newRoom->id = ((Room)room)->id;
	newRoom->faculty = ((Room)room)->faculty;
	newRoom->price = ((Room)room)->price;
	newRoom->num_ppl = ((Room)room)->num_ppl;
	newRoom->from_hrs = ((Room)room)->from_hrs;
	newRoom->to_hrs = ((Room)room)->to_hrs;
	newRoom->difficulty = ((Room)room)->difficulty;
	return newRoom;
}

void freeRoom(SetElement room){
	if ( room == NULL ) return;
	free(((Room)room)->email);
	free((Room)room);
}

int compareRooms(const SetElement room1, const SetElement room2) {
	//TODO email to faculty
	if ( room1 == NULL || room2 == NULL ) {
		//TODO print that is null;
		return 0;
	}
	//int emailCompare = strcmp( ((Room)room1)->email, ((Room)room2)->email );
	int facultyCompare = (((Room)room1)->faculty - ((Room)room2)->faculty);
	if ( facultyCompare == 0 ) {
		return ( ((Room)room1)->id - ((Room)room2)->id );
	} else {
		return facultyCompare;
	}
}

MtmErrorCode createRoom(Room newRoom, const char* email, int id, int faculty, int price, int num_ppl, const char* working_hrs, int difficulty) {
	newRoom->email = malloc(sizeof(char) * (strlen(email)+1));
	if ( newRoom->email == NULL) {
		free(newRoom);
		return MTM_OUT_OF_MEMORY;
	}
	if ( id < 1 || price < 1 || price % 4 != 0 || num_ppl < 1) {
		free(newRoom->email);
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}

	int from =  fromHour(working_hrs);
	int to =  toHour(working_hrs);
//TODO open till 24?
	if ( from < 0 || from >= to || to > 23) {
		free(newRoom->email);
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}

	if ( difficulty < 1 || difficulty > 10 ) {
		free(newRoom->email);
		free(newRoom);
		return MTM_INVALID_PARAMETER;
	}

	strcpy(newRoom->email, email);
	newRoom->id = id;
	newRoom->faculty = faculty;
	newRoom->price = price;
	newRoom->num_ppl = num_ppl;
	newRoom->from_hrs = from;
	newRoom->to_hrs = to;
	newRoom->difficulty = difficulty;
	return MTM_SUCCESS;
}

int calculatePriceOfOrder(const Room room, TechnionFaculty escaperFaculty, int num_ppl) {
	//TODO maybe doesn't test return value
	if( escaperFaculty == UNKNOWN ) return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
	//TODO maybe doesn't test return value
	if ( room == NULL ) return MTM_ID_DOES_NOT_EXIST;

	if ( ((Room)room)->faculty == escaperFaculty ) return ((((Room)room)->price * 75) / 100) * num_ppl;
	return returnRoomPrice( room ) * num_ppl;
}

int returnRoomPrice(const Room room) {
	if( room != NULL ) return room->price;
	return -1;
}


void printRoom(const SetElement setElement) {
	printf("\nRoom print\n");
	printf("  Room email: %s\n", ((Room)setElement)->email );
	printf("  Room faculty: %d / id: %d\n", ((Room)setElement)->faculty, ((Room)setElement)->id);
	printf("  Room open hours: %d - id: %d\n", ((Room)setElement)->from_hrs, ((Room)setElement)->to_hrs);
	printf("  Room num_ppl: %d\n", ((Room)setElement)->num_ppl);
	printf("  Room difficulty: %d\n", ((Room)setElement)->difficulty);
	printf("  Room price: %d\n", ((Room)setElement)->price);
	return;
}


int fromHour(const char* working_hrs) {
	return ( charToInt(working_hrs[1]) + ( charToInt(working_hrs[0]) * 10 ));
}

int toHour(const char* working_hrs) {
	return ( charToInt(working_hrs[4]) + ( charToInt(working_hrs[3]) * 10 ));
}

int charToInt(char c) {
	return (c - (int)'0');
}

int filterByNumOfPplandDifficulty(const SetElement setElement, SetKey num_ppl, SetKey skill_level ) {
	return (pow(((Room)setElement)->num_ppl-num_ppl,2) + (pow(((Room)setElement)->difficulty - skill_level,2 )) );
}

int filterByNearFaculty(const SetElement setElement, SetKey faculty, SetKey junk ) {
	return abs(((Room)setElement)->faculty - faculty);
}

int filterByNearId(const SetElement setElement, SetKey id, SetKey junk ) {
	return abs(((Room)setElement)->id - id);
}
