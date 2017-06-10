#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdio.h> //TODO remove it
#include <stdlib.h>

#include "escaper.h"
#include "faculty.h"
#include "company.h"
#include "room.h"
#include "order.h"
#include "common.h"

typedef struct EscapeSystem_t {
	Set escapers;
	Set companies;
	Set rooms;
	List days;
	List faculties;
} *EscapeSystem;




MtmErrorCode createSystem(EscapeSystem sys);

MtmErrorCode destroySystem(EscapeSystem sys);




MtmErrorCode addCompany(EscapeSystem sys, const char* email, TechnionFaculty faculty);

MtmErrorCode removeCompany(EscapeSystem sys, const char* email);

SetElement findCompanyByEmail(const EscapeSystem sys, const char* email);

bool isAnyRoomOfACompanyOrdered(const EscapeSystem sys, const char* email);



MtmErrorCode addAnEscaper(EscapeSystem sys, const char* email, TechnionFaculty faculty, SkillLevel typeSkill);

MtmErrorCode removeAnEscaper(EscapeSystem sys, const char* email);

SetElement findEscaperByEmail(const EscapeSystem sys, const char* email );

bool isEscaperAvailable(const EscapeSystem sys, int daysFromToday, int hour, SetElement escaper);



//TODO working hours should be const
MtmErrorCode addARoom(EscapeSystem sys, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty);

MtmErrorCode removeARoom(EscapeSystem sys, TechnionFaculty faculty, int id);

MtmErrorCode removeAllRoomsOfCompany(EscapeSystem sys, const char* companyEmail);

SetElement findRoom(const EscapeSystem sys, TechnionFaculty faculty, int id);

Room findRecommendedRoom(const EscapeSystem sys, const Escaper escaper, int  num_ppl);

bool isRoomAvailable(const EscapeSystem sys, int daysFromToday, int hour, ListElement room);

Set filterRoomSet(const Set rooms, RecommendSetElement recommendSetElement, SetKey key1, SetKey key2 );





MtmErrorCode addAnOrder(EscapeSystem sys, const char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl);

MtmErrorCode addRecommendedOrder(EscapeSystem sys, char* email, int num_ppl);

MtmErrorCode addFirstAvailableOrder(EscapeSystem sys, Order order, SetElement room, SetElement escaper );

bool IsARoomOrdered(const EscapeSystem sys, TechnionFaculty faculty, int id);

Day returnADayFromToday(const EscapeSystem sys, int daysFromToday);

MtmErrorCode markAsRemovedOrdersOfEscaper(EscapeSystem sys, const char* email );


List createFaculties(int numberOfFaculties);

Faculty findFacultyByNumber(List Faculties, TechnionFaculty facultyNumber);

List returnListOfBestNFaculties(List faculties, int number);

int returnTotalFacultiesRevenue(List faculties);




MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem system);

MtmErrorCode reportBest(FILE* outputChannel, EscapeSystem system);














#endif /* SYSTEM_H_ */




