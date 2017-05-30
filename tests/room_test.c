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

	ASSERT_TEST( compareRooms(room, newRoom) == 0 );

	char* email2 = "qazxsw@edcvfp";
	free(room->email);
	room->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(room->email, email2);

	ASSERT_TEST( compareRooms(room, newRoom) != 0 );

	free(newRoom->email);
	free(newRoom);

	free(room->email);
	free(room);

	return true;
}

static bool testAddRoom() {

	Set companies = setCreate(copyCompany, freeCompany, compareCompanies);
	ASSERT_TEST( companies != NULL);

	ASSERT_TEST( setGetSize(companies) == 0 );

	addCompany( companies, "sdfefdgdfh565@654fgjhfgsda", CIVIL_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdb", MECHANICAL_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdc", ELECTRICAL_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdd", CHEMICAL_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsde", BIOTECHNOLOGY_AND_FOOD_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdf", AEROSPACE_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdg", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdh", MATHEMATICS);



	Set rooms = setCreate(copyRoom, freeRoom, compareRooms);
	ASSERT_TEST( rooms != NULL);

	ASSERT_TEST( setGetSize(rooms) == 0 );
	//TODO check email validity
	addRoom(rooms, companies, "sdfefdgdfh565@654fgjhfgsda", 0, 1, 3, 5, 7, 10);

	ASSERT_TEST( setGetSize(rooms) == 1 );

	addRoom(rooms, companies, "sdfefdgdfh5654654fgjhfgsdf", 0, 1, 3, 5, 7, 10);

	ASSERT_TEST( setGetSize(rooms) == 1 );

	addRoom(rooms, companies, "sdfefdgdfh5654654fgjhfgsdg", 0, 1, 3, 5, 7, 10);

	ASSERT_TEST( setGetSize(rooms) == 2 );

	setClear(rooms);

	ASSERT_TEST( setGetSize(rooms) == 0 );

	setDestroy(rooms);

	return true;
}

static bool testOtherSetRoomFunctions() {
	Set rooms = setCreate(copyRoom, freeRoom, compareRooms);
	ASSERT_TEST( rooms != NULL);

	Set companies = setCreate(copyCompany, freeCompany, compareCompanies);
	ASSERT_TEST( companies != NULL);

	ASSERT_TEST( setGetSize(companies) == 0 );

	addCompany( companies, "sdfefdgdfh565@654fgjhfgsda", CIVIL_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdb", MECHANICAL_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdc", ELECTRICAL_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdd", CHEMICAL_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsde", BIOTECHNOLOGY_AND_FOOD_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdf", AEROSPACE_ENGINEERING);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdg", INDUSTRIAL_ENGINEERING_AND_MANAGEMENT);
	addCompany( companies, "sdfefdgdfh565@654fgjhfgsdh", MATHEMATICS);


	Room room1 = malloc(sizeof(struct room_t));
	char* email1 = "sdfefdgdfh565@154fgjhfgsda";
	room1->email = malloc(sizeof(char) * (strlen(email1) + 1));
	strcpy(room1->email, email1);
	room1->id = 1;
	room1->price = 10;
	room1->num_ppl = 4;
	room1->from_hrs = 3;
	room1->to_hrs = 7;
	room1->difficulty = 5;

	Room room2 = malloc(sizeof(struct room_t));
	char* email2 = "sdfefdgdfh565@254fgjhfgsda";
	room2->email = malloc(sizeof(char) * (strlen(email2) + 1));
	strcpy(room2->email, email2);
	room2->id = 1;
	room2->price = 10;
	room2->num_ppl = 4;
	room2->from_hrs = 3;
	room2->to_hrs = 7;
	room2->difficulty = 5;

	Room room3 = malloc(sizeof(struct room_t));
	char* email3 = "sdfefdgdfh565@354fgjhfgsda";
	room3->email = malloc(sizeof(char) * (strlen(email3) + 1));
	strcpy(room3->email, email1);
	room3->id = 1;
	room3->price = 10;
	room3->num_ppl = 4;
	room3->from_hrs = 3;
	room3->to_hrs = 7;
	room3->difficulty = 5;

	Room room4 = malloc(sizeof(struct room_t));
	char* email4 = "sdfefdgdfh565@454fgjhfgsda";
	room4->email = malloc(sizeof(char) * (strlen(email4) + 1));
	strcpy(room4->email, email1);
	room4->id = 1;
	room4->price = 10;
	room4->num_ppl = 4;
	room4->from_hrs = 3;
	room4->to_hrs = 7;
	room4->difficulty = 5;

	addRoom(rooms, companies, "sdfefdgdfh565@154fgjhfgsda", 1, 1, 3, 5, 7, 10);
	addRoom(rooms, companies, "sdfefdgdfh565@254fgjhfgsda", 1, 1, 3, 5, 7, 10);
	addRoom(rooms, companies, "sdfefdgdfh565@354fgjhfgsda", 1, 1, 3, 5, 7, 10);
	addRoom(rooms, companies, "sdfefdgdfh565@454fgjhfgsda", 1, 1, 3, 5, 7, 10);

	ASSERT_TEST( setGetSize(rooms) == 4 );

	ASSERT_TEST( setIsIn(rooms, room1) );
	ASSERT_TEST( setIsIn(rooms, room2) );
	ASSERT_TEST( setIsIn(rooms, room3) );
	ASSERT_TEST( setIsIn(rooms, room4) );

	Set newCompanies = setCopy(rooms);

	ASSERT_TEST( setIsIn(newCompanies, room1) );
	ASSERT_TEST( setIsIn(newCompanies, room2) );
	ASSERT_TEST( setIsIn(newCompanies, room3) );
	ASSERT_TEST( setIsIn(newCompanies, room4) );

	ASSERT_TEST( setGetSize(newCompanies) == 4 );

	freeRoom(room1);
	freeRoom(room2);
	freeRoom(room3);
	freeRoom(room4);
	setDestroy(rooms);
	setDestroy(newCompanies);
	return true;
}

int main (int argv, char** arc) {
	RUN_TEST(testCopyRoom);
	RUN_TEST(testFreeRoom);
	RUN_TEST(testCompareRoom);
	RUN_TEST(testAddRoom);
	RUN_TEST(testOtherSetRoomFunctions);


	return 0;
}
