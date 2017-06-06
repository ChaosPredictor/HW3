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

MtmErrorCode createSystem(EscapeSystem **sys);

MtmErrorCode destroySystem(EscapeSystem *sys);

MtmErrorCode createCompanySet(EscapeSystem* sys);


MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem system);

MtmErrorCode reportBest(FILE* outputChannel, EscapeSystem system);

#endif /* SYSTEM_H_ */




