/*
 * room.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */


#include "room.h"

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

int compareRooms(SetElement room1, SetElement room2) {
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

/* moved toi system
MtmErrorCode addRoom(Set rooms, Set users, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty) {
	if ( rooms == NULL || users == NULL ) return MTM_INVALID_PARAMETER;
	if ( email == NULL || !emailValidity(email) )  return MTM_INVALID_PARAMETER;

	TechnionFaculty faculty = findCompanyFacultyFromEmail(users, email);
	if ( faculty == UNKNOWN ) return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;


	//TODO check email exist
	//TODO check email not in the list
	//TODO faculty & id unic
	Room newRoom = malloc(sizeof(struct room_t));
	if ( newRoom == NULL) {
		return MTM_OUT_OF_MEMORY;
	}
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
//TODO open till 24
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
	//printf("faculty: %d id: %d\n", faculty, id);
	if( setIsIn(rooms, newRoom) ) {
		free(newRoom->email);
		free(newRoom);
		return MTM_ID_ALREADY_EXIST;
	}

	setAdd(rooms, newRoom);
	free(newRoom->email);
	free(newRoom);
	return MTM_SUCCESS;
}
*/





MtmErrorCode createRoom(Room newRoom, const char* email, int id, int faculty, int price, int num_ppl, char* working_hrs, int difficulty) {
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
//TODO open till 24
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


/* moved to system
MtmErrorCode removeRoom(Set setRoom, TechnionFaculty faculty, int id) {
	if( setRoom == NULL ) return MTM_INVALID_PARAMETER;
	if( faculty < 0 || faculty > 17 ) return MTM_INVALID_PARAMETER;
	if( id < 1 ) return MTM_INVALID_PARAMETER;
	//TODO not remove company with order
	SET_FOREACH(Room, val, setRoom) {
		if ( val->faculty == faculty && val->id == id ) {
			//TODO if is order
			if ( false ) {
				return MTM_RESERVATION_EXISTS;
			} else {
				//TODO remove all rooms
				setRemove(setRoom, val);
				return MTM_SUCCESS;
			}
		}
	}
	return MTM_ID_DOES_NOT_EXIST;
}*/


Set filterRoomSet(Set rooms, RecommendSetElement recommendSetElement, SetKey num_ppl, SetKey skill_level ) {
	Room room = setGetFirst(rooms);
	//User user = findUserFromEmail( users, email );
	long int minValue = -1, tempValue;
	Set recommendedRooms = setCreate(copyRoom, freeRoom, compareRooms);
	while ( room != NULL ) {
		tempValue = recommendSetElement( room, num_ppl, skill_level);
		//tempValue = ( (pow(room->num_ppl-num_ppl,2) + (pow(room->difficulty - user->typeSkill,2 )) );
		if ( tempValue < minValue || minValue == -1) {
			minValue = tempValue;
			setClear(recommendedRooms);
			setAdd(recommendedRooms, room);
		} else if ( tempValue == minValue ) {
			setAdd(recommendedRooms, room);
		}
		room = setGetNext(rooms);
	}
	return recommendedRooms;
}


int getRoomPrice(const Set rooms, TechnionFaculty faculty, int id) {
	Room room = findRoom(rooms, faculty, id);
	if( room != NULL ) return room->price;
	return -1;
}


int getTotalRoomPrice(const SetElement room, TechnionFaculty faculty) {
	if ( ((Room)room)->faculty == faculty ) return ((((Room)room)->price * 75) / 100) ;
	return ((Room)room)->price;
}

SetElement findRoom(const Set rooms, TechnionFaculty faculty, int id) {
	SET_FOREACH(Room, val, rooms) {
		if ( val->faculty == faculty && val->id == id ) {
			return val;
		}
	}
	return NULL;
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

int recommendByNumOfPplandDifficulty(const SetElement setElement, SetKey num_ppl, SetKey skill_level ) {
	return (pow(((Room)setElement)->num_ppl-num_ppl,2) + (pow(((Room)setElement)->difficulty - skill_level,2 )) );
}

int recommendByNearFaculty(const SetElement setElement, SetKey faculty, SetKey junk ) {
	return abs(((Room)setElement)->faculty - faculty);
}

int recommendByNearId(const SetElement setElement, SetKey id, SetKey junk ) {
	return abs(((Room)setElement)->id - id);
}
