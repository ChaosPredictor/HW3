#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdio.h> //TODO remove it
#include <stdlib.h>

#include "user.h"
#include "faculty.h"

//typedef struct EscapeSystem_t EscapeSystem;


typedef struct EscapeSystem_t {
	Set users;
	Set rooms;
	List days;
	List faculties;
} *EscapeSystem;


typedef enum {
    COMPANY,
	ESCAPER_1,
	ESCAPER_2,
	ESCAPER_3,
	ESCAPER_4,
	ESCAPER_5,
	ESCAPER_6,
	ESCAPER_7,
	ESCAPER_8,
	ESCAPER_9,
	ESCAPER_10
} TypeSkill;


MtmErrorCode createSystem(EscapeSystem **sys);

MtmErrorCode destroySystem(EscapeSystem *sys);

MtmErrorCode createCompanySet(EscapeSystem* sys);




MtmErrorCode addUser(EscapeSystem sys, const char* email, TechnionFaculty faculty, TypeSkill typeSkill);

MtmErrorCode removeCompany(EscapeSystem sys, const char* email);





MtmErrorCode removeEscaper(EscapeSystem sys, const char* email);



//TODO working hours should be const
MtmErrorCode addRoom(EscapeSystem sys, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty);

MtmErrorCode removeRoom(EscapeSystem sys, TechnionFaculty faculty, int id);



MtmErrorCode addOrder(EscapeSystem sys, char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl);



MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem system);

MtmErrorCode reportBest(FILE* outputChannel, EscapeSystem system);






#endif /* SYSTEM_H_ */




