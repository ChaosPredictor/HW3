#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdio.h> //TODO remove it
#include <stdlib.h>
#include "escaper.h"
#include "faculty.h"
#include "company.h"
#include "room.h"
#include "order.h"
#include "mtm_ex3.h"

typedef struct EscapeSystem_t {
	Set escapers;
	Set companies;
	Set rooms;
	List days;
	List faculties;
} *EscapeSystem;




MtmErrorCode createSystem(EscapeSystem sys);

MtmErrorCode destroySystem(EscapeSystem sys);

MtmErrorCode inputChannelSelector(int argc, char* argv[], FILE** channelIn, FILE** channelOut );

MtmErrorCode sellectBothFiles(char* argv[], FILE** channelIn, FILE** channelOut);

MtmErrorCode sellectOneOfTheFiles(char* argv[], FILE** channelIn, FILE** channelOut);

MtmErrorCode openAllFiles(const char *inFile, const char *outFile, FILE** channelIn, FILE** channelOut);

char* addInSuffix(const char* string);

char* addOutSuffix(const char* string);

char* addErrSuffix(const char* string);

void freeAllNames(char *in, char *out, char *err);


MtmErrorCode addCompany(EscapeSystem sys, const char* email, TechnionFaculty faculty);

MtmErrorCode removeCompany(EscapeSystem sys, const char* email);

Company findCompanyByEmail(const EscapeSystem sys, const char* email);

bool isAnyRoomOfACompanyOrdered(const EscapeSystem sys, const char* email);



MtmErrorCode addEscaper(EscapeSystem sys, const char* email, TechnionFaculty faculty, SkillLevel typeSkill);

MtmErrorCode removeEscaper(EscapeSystem sys, const char* email);

Escaper findEscaperByEmail(const EscapeSystem sys, const char* email );

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

MtmErrorCode removedOrdersOfEscaper(EscapeSystem sys, const char* email );


List createFaculties(int numberOfFaculties);

Faculty findFacultyByNumber(List Faculties, TechnionFaculty facultyNumber);

List returnListOfBestNFaculties(List faculties, int number);

int returnTotalFacultiesRevenue(List faculties);




MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem system);

MtmErrorCode reportBest(FILE* outputChannel, EscapeSystem system);














#endif /* SYSTEM_H_ */




