/*
 * room.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */


#include "room.h"

struct room_t {
	char* email;
	int id;
	TechnionFaculty faculty;
	int price;
	int num_ppl;
	int from_hrs, to_hrs;
	int difficulty;
};


MtmErrorCode addRoom(Set rooms, Set companies , char* email, int id, int price, int num_ppl, int from_hrs, int to_hrs, int difficulty) {
	//TODO check email exist
	//TODO check email not in the list
	//TODO faculty & id unic
	Room newRoom = malloc(sizeof(struct room_t));
	newRoom->email = malloc(sizeof(char) * (strlen(email)+1));
	strcpy(newRoom->email, email);
	newRoom->id = id;
	newRoom->faculty = findFacultyFromEmail(companies, email);
	newRoom->price = price;
	newRoom->num_ppl = num_ppl;
	newRoom->from_hrs = from_hrs;
	newRoom->to_hrs = to_hrs;
	newRoom->difficulty = difficulty;
	setAdd(rooms, newRoom);
	free(newRoom->email);
	free(newRoom);
	return MTM_SUCCESS;
}


MtmErrorCode removeRoom(Set setRoom, TechnionFaculty faculty, int id) {
	//TODO check email exist
	//TODO check email not in the list
	//TODO find rigth room
	//TODO remove the room
	return MTM_SUCCESS;
}


SetElement copyRoom(SetElement room){
	if ( room == NULL ) return NULL;
	//TODO maybe assert
	Room newRoom = malloc(sizeof(struct room_t));
	//TODO return from malloc

	newRoom->email = malloc(sizeof(char) * (strlen(((Room)room)->email) + 1));
	//TODO return from malloc

	strcpy(newRoom->email, ((Room)room)->email);

	newRoom->id = ((Room)room)->id;
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

int compareRooms(SetElement room1, SetElement room2) {
	//TODO email to faculty
	if ( room1 == NULL || room2 == NULL ) {
		//TODO print that is null;
		return 0;
	}
	int emailCompare = strcmp( ((Room)room1)->email, ((Room)room2)->email );

	if ( emailCompare == 0 ) {
		return ( ((Room)room1)->id - ((Room)room2)->id );
	} else {
		return emailCompare;
	}
}

