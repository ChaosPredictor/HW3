#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdio.h> //TODO remove it
#include <stdlib.h>

#include "escaper.h"
#include "faculty.h"
#include "company.h"

//typedef struct EscapeSystem_t EscapeSystem;


typedef struct EscapeSystem_t {
	Set escapers;
	Set companies;
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




MtmErrorCode addCompany(EscapeSystem sys, const char* email, TechnionFaculty faculty);

MtmErrorCode removeCompany(EscapeSystem sys, const char* email);

SetElement findCompanyByEmail( Set setCompany, const char* email );



MtmErrorCode addEscaper(EscapeSystem sys, const char* email, TechnionFaculty faculty, TypeSkill typeSkill);

MtmErrorCode removeEscaper(EscapeSystem sys, const char* email);

SetElement findEscaperByEmail( Set setEscaper, const char* email );



//TODO working hours should be const
MtmErrorCode addRoom(EscapeSystem sys, const char* email, int id, int price, int num_ppl, char* working_hrs, int difficulty);

MtmErrorCode removeRoom(EscapeSystem sys, TechnionFaculty faculty, int id);



MtmErrorCode addOrder(EscapeSystem sys, char* email, TechnionFaculty faculty, int id, const char* time, int num_ppl);

MtmErrorCode addRecommendedOrder(EscapeSystem sys, char* email, int num_ppl);


MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem system);

MtmErrorCode reportBest(FILE* outputChannel, EscapeSystem system);




bool emailValidity(const char* email);







#endif /* SYSTEM_H_ */




