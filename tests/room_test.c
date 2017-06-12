/*
 * room_test.c
 *
 *  Created on: May 30, 2017
 *      Author: master
 */


#include "./room_test.h"


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

	room->faculty = 2;

	ASSERT_TEST( compareRooms(room, newRoom) != 0 );

	free(newRoom->email);
	free(newRoom);

	free(room->email);
	free(room);

	return true;
}


static bool testCreateRoom() {
	Room newRoom = malloc(sizeof(struct room_t));

	char* email = "company1@civil";
	char* invalidEmail = "company1#civil";

	ASSERT_TEST( createRoom(newRoom, invalidEmail, 1, 0, 40, 3, 5, 8, 5) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( createRoom(newRoom, email, 1, 0, 41, 3, 5, 8, 5) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( createRoom(newRoom, email, 1, 0, 40, 3, 8, 8, 5) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( createRoom(newRoom, email, 1, 0, 40, 3, 8, 25, 5) == MTM_INVALID_PARAMETER );
	ASSERT_TEST( createRoom(newRoom, email, 1, 0, 40, 3, 8, 23, 0) == MTM_INVALID_PARAMETER );

	ASSERT_TEST( createRoom(newRoom, email, 1, 0, 40, 3, 5, 8, 5) == MTM_SUCCESS );


	freeRoom(newRoom);

	return true;
}

static bool testCalculatePriceOfOrder() {
	Room newRoom = malloc(sizeof(struct room_t));

	char* email = "company1@civil";

	ASSERT_TEST( createRoom(newRoom, email, 1, 0, 40, 3, 5, 8, 5) == MTM_SUCCESS );

	ASSERT_TEST( calculatePriceOfOrder(newRoom, 0, 3) == 90 );
	ASSERT_TEST( calculatePriceOfOrder(newRoom, 1, 3) == 120 );
	ASSERT_TEST( calculatePriceOfOrder(newRoom, 0, 4) == 120 );

	freeRoom(newRoom);
	return true;
}




int roomTests () {
	printf("\n\n ================ Room Tests ================ \n\n");
	RUN_TEST(testCopyRoom);
	RUN_TEST(testFreeRoom);
	RUN_TEST(testCompareRoom);
	RUN_TEST(testCreateRoom);
	RUN_TEST(testCalculatePriceOfOrder);

	return 0;
}
