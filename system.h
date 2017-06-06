#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdio.h> //TODO remove it
#include <stdlib.h>

#include "user.h"

//typedef struct EscapeSystem_t EscapeSystem;


typedef struct EscapeSystem_t
{
	Set users;
	Set rooms;
	List days;
} *EscapeSystem;

MtmErrorCode createSystem(EscapeSystem **sys);

MtmErrorCode destroySystem(EscapeSystem *sys);

MtmErrorCode createCompanySet(EscapeSystem* sys);


MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem system);


#endif /* SYSTEM_H_ */




