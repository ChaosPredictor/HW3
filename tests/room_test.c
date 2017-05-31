/*
 * room_test.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */


#include "./test_utilities.h"
#include "./../room.c"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./../mtm_escape.h"
#include <string.h>
#include <ctype.h>
#include "./../room.h"
#include "./../company.h"

static bool testCopyRoom() {

	ASSERT_TEST( copyRoom(NULL) == NULL);

	Room room = malloc(sizeof(struct room_t));
	char* email = "qazxsw@edcvfr";
	room->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(room->email, email);
	room->id = 1;
	room->price = 10;
	room->num_ppl = 4;
	room->from_hrs = 3;
	room->to_hrs = 7;
	room->difficulty = 5;

	Room newRoom = copyRoom(room);

	ASSERT_TEST( newRoom != NULL);
	ASSERT_TEST( strcmp(room->email,newRoom->email) == 0);
	ASSERT_TEST( room->id == newRoom->id );
	ASSERT_TEST( room->price == newRoom->price );
	ASSERT_TEST( room->num_ppl == newRoom->num_ppl );
	ASSERT_TEST( room->from_hrs == newRoom->from_hrs );
	ASSERT_TEST( room->to_hrs == newRoom->to_hrs );
	ASSERT_TEST( room->difficulty == newRoom->difficulty );



	free(newRoom->email);
	free(newRoom);

	free(room->email);
	free(room);

	return true;
}

static bool testFreeRoom() {

	//ASSERT_TEST( freeRoom(NULL) == NULL);
	freeRoom(NULL);

	Room room = malloc(sizeof(struct room_t));
	char* email = "qazxsw@edcvfr";
	room->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(room->email, email);
	room->id = 1;
	room->price = 10;
	room->num_ppl = 4;
	room->from_hrs = 3;
	room->to_hrs = 7;
	room->difficulty = 5;

	Room newRoom = copyRoom(room);

	freeRoom(newRoom);
	freeRoom(room);

	return true;
}

static bool testCompareRoom() {

	ASSERT_TEST( copyRoom(NULL) == NULL);

	Room room = malloc(sizeof(struct room_t));
	char* email = "qazxsw@edcvfr";
	room->email = malloc(sizeof(char) * (strlen(email) + 1));
	strcpy(room->email, email);
	room->id = 1;
	room->faculty = 1;
	room->price = 10;
	room->num_ppl = 4;
	room->from_hrs = 3;
	room->to_hrs = 7;
	room->difficulty = 5;

	Room newRoom = copyRoom(room);

	ASSERT_TEST( newRoom != NULL);
	ASSERT_TEST( strcmp(room->email,newRoom->email) == 0);
	ASSERT_TEST( room->faculty == newRoom->faculty );
	ASSERT_TEST( room->id == newRoom->id );
	ASSERT_TEST( room->price == newRoom->price );
	ASSERT_TEST( room->num_ppl == newRoom->num_ppl );
	ASSERT_TEST( room->from_hrs == newRoom->from_hrs );
	ASSERT_TEST( room->to_hrs == newRoom->to_hrs );
	ASSERT_TEST( room->difficulty == newRoom->difficulty );

	ASSERT_TEST( compareRooms(room, newRoom) == 0 );

	//char* email2 = "qazxsw@edcvfp";
	//free(room->email);
	//room->email = malloc(sizeof(char) * (strlen(email2) + 1));
	//strcpy(room->email, email2);

	room->faculty = 2;

	ASSERT_TEST( compareRooms(room, newRoom) != 0 );

	free(newRoom->email);
	free(newRoom);

	free(room->email);
	free(room);

	return true;
}
/*
static Set testHelperAddUsers() {
	Set users = setCreate(copyUser, freeUser, compareUsers);
	ASSERT_TEST( users != NULL);
	ASSERT_TEST( setGetSize(users) == 0 );

	addUser( users, "company1@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "company1@mechanical", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@electrical", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@chemical", CHEMICAL_ENGINEERING, COMPANY );
	addUser( users, "company1@biotechnology", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, COMPANY );
	addUser( users, "company1@aerospace", AEROSPACE_ENGINEERING, COMPANY );
	addUser( users, "company1@industrial", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT, COMPANY );
	addUser( users, "company1@mathematics", MATHEMATICS, COMPANY );
	addUser( users, "company2@civil", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "escaper1@civil", CIVIL_ENGINEERING, ESCAPER_1 );
	addUser( users, "escaper2@civil", CIVIL_ENGINEERING, ESCAPER_5 );
	return users;
}*/

static bool testAddRoom() {
	Set users = testHelperAddUsers();

	Set rooms = setCreate(copyRoom, freeRoom, compareRooms);
	ASSERT_TEST( rooms != NULL);

	addRoom(NULL, users, "sdfefdgdfh565#654fgjhfgsda", 1, 1, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, NULL, "sdfefdgdfh565#654fgjhfgsda", 1, 1, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, NULL, 0, 1, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//illegal email
	addRoom(rooms, users, "sdfefdgdfh565#654fgjhfgsda", 1, 1, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//company email does not exist
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsdz", 1, 1, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//0 & -1 id
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsdg", 0, 1, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsdg", -1, 1, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//price
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 0, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, -1, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 3, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//num_ppl
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, 0, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, -1, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//working hours
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, 3, "07-05", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, 3, "05-05", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, 3, "05-24", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, 3, "24-05", 10);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	//difficulty
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, 3, "05-07", 0);
	ASSERT_TEST( setGetSize(rooms) == 0 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, 3, "05-07", 11);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "05-07", 10) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(rooms) == 1 );

	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 4, 3, "05-07", 10) == MTM_ID_ALREADY_EXIST );
	ASSERT_TEST( setGetSize(rooms) == 1 );

	//price
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 1, 1, 3, "05-07", 10) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( setGetSize(rooms) == 1 );

	//same faculty, different id
	ASSERT_TEST( addRoom(rooms, users, "company1@civil", 2, 4, 3, "05-07", 10) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(rooms) == 2 );

	//same id, different faculty
	ASSERT_TEST( addRoom(rooms, users, "company1@mechanical", 1, 4, 3, "05-07", 10) == MTM_SUCCESS );
	ASSERT_TEST( setGetSize(rooms) == 3 );

	//fail case different company same faculty
	ASSERT_TEST( addRoom(rooms, users, "company2@civil", 1, 4, 3, "05-07", 10) == MTM_ID_ALREADY_EXIST );
	ASSERT_TEST( setGetSize(rooms) == 3 );

	setClear(rooms);

	ASSERT_TEST( setGetSize(rooms) == 0 );

	setDestroy(users);
	setDestroy(rooms);

	return true;
}

static bool testRemoveRoom() {
	Set users = setCreate(copyUser, freeUser, compareUsers);
	ASSERT_TEST( users != NULL);

	ASSERT_TEST( setGetSize(users) == 0 );

	addUser( users, "sdfefdgdfh565@654fgjhfgsda", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdb", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdc", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdd", CHEMICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsde", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdf", AEROSPACE_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdg", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdh", MATHEMATICS, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdi", CIVIL_ENGINEERING, COMPANY );

	Set rooms = setCreate(copyRoom, freeRoom, compareRooms);
	ASSERT_TEST( rooms != NULL);

	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 4, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 1 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 2, 8, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 2 );
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsdg", 1, 12, 3, "05-07", 10);
	ASSERT_TEST( setGetSize(rooms) == 3 );

	removeRoom(rooms, CIVIL_ENGINEERING, 1);
	ASSERT_TEST( setGetSize(rooms) == 2 );

	removeRoom(rooms, CIVIL_ENGINEERING, 2);
	ASSERT_TEST( setGetSize(rooms) == 1 );

	removeRoom(rooms, INDUSTRIAL_ENGINEERING_AND_MANAGEMENT, 1);
	ASSERT_TEST( setGetSize(rooms) == 0 );

	setClear(rooms);

	ASSERT_TEST( setGetSize(rooms) == 0 );

	setDestroy(users);
	setDestroy(rooms);

	return true;
}



static bool testOtherSetRoomFunctions() {
	Set rooms = setCreate(copyRoom, freeRoom, compareRooms);
	ASSERT_TEST( rooms != NULL);

	Set users = setCreate(copyUser, freeUser, compareUsers);
	ASSERT_TEST( users != NULL);

	ASSERT_TEST( setGetSize(users) == 0 );

	addUser( users, "sdfefdgdfh565@654fgjhfgsda", CIVIL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdb", MECHANICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdc", ELECTRICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdd", CHEMICAL_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsde", BIOTECHNOLOGY_AND_FOOD_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdf", AEROSPACE_ENGINEERING, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdg", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT, COMPANY );
	addUser( users, "sdfefdgdfh565@654fgjhfgsdh", MATHEMATICS, COMPANY );

	Room room1 = malloc(sizeof(struct room_t));
	char* email1 = "sdfefdgdfh565@654fgjhfgsda";
	room1->email = malloc(sizeof(char) * (strlen(email1) + 1));
	strcpy(room1->email, email1);
	room1->id = 1;
	room1->faculty = CIVIL_ENGINEERING;
	room1->price = 10;
	room1->num_ppl = 4;
	room1->from_hrs = 3;
	room1->to_hrs = 7;
	room1->difficulty = 5;

	Room room2 = malloc(sizeof(struct room_t));
	char* email2 = "sdfefdgdfh565@654fgjhfgsdd";
	room2->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(room2->email, email2);
	room2->id = 2;
	room2->faculty = MECHANICAL_ENGINEERING;
	room2->price = 10;
	room2->num_ppl = 4;
	room2->from_hrs = 3;
	room2->to_hrs = 7;
	room2->difficulty = 5;

	Room room3 = malloc(sizeof(struct room_t));
	char* email3 = "sdfefdgdfh565@654fgjhfgsdc";
	room3->email = malloc(sizeof(char) * (strlen(email3) + 1));
	strcpy(room3->email, email1);
	room3->id = 3;
	room3->faculty = ELECTRICAL_ENGINEERING;
	room3->price = 10;
	room3->num_ppl = 4;
	room3->from_hrs = 3;
	room3->to_hrs = 7;
	room3->difficulty = 5;

	Room room4 = malloc(sizeof(struct room_t));
	char* email4 = "sdfefdgdfh565@654fgjhfgsdd";
	room4->email = malloc(sizeof(char) * (strlen(email4) + 1));
	strcpy(room4->email, email1);
	room4->id = 4;
	room4->faculty = CHEMICAL_ENGINEERING;
	room4->price = 10;
	room4->num_ppl = 4;
	room4->from_hrs = 3;
	room4->to_hrs = 7;
	room4->difficulty = 5;

	//int r;
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsda", 1, 40, 3, "05-07", 10);
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsdb", 2, 36, 3, "05-07", 10);
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsdc", 3, 32, 3, "05-07", 10);
	addRoom(rooms, users, "sdfefdgdfh565@654fgjhfgsdd", 4, 28, 3, "05-07", 10);
	//printf("result: %d", r);
	ASSERT_TEST( setGetSize(rooms) == 4 );

	ASSERT_TEST( setIsIn(rooms, room1) );
	ASSERT_TEST( setIsIn(rooms, room2) );
	ASSERT_TEST( setIsIn(rooms, room3) );
	ASSERT_TEST( setIsIn(rooms, room4) );

	Set newRooms = setCopy(rooms);

	ASSERT_TEST( setGetSize(newRooms) == 4 );

	ASSERT_TEST( setIsIn(newRooms, room1) );
	ASSERT_TEST( setIsIn(newRooms, room2) );
	ASSERT_TEST( setIsIn(newRooms, room3) );
	ASSERT_TEST( setIsIn(newRooms, room4) );


	freeRoom(room1);
	freeRoom(room2);
	freeRoom(room3);
	freeRoom(room4);

	setDestroy(users);
	setDestroy(rooms);
	setDestroy(newRooms);
	return true;
}

int roomTests (int argv, char** arc) {
//int main (int argv, char** arc) {
	RUN_TEST(testCopyRoom);
	RUN_TEST(testFreeRoom);
	RUN_TEST(testCompareRoom);
	RUN_TEST(testAddRoom);
	RUN_TEST(testRemoveRoom);
	RUN_TEST(testOtherSetRoomFunctions);


	return 0;
}
