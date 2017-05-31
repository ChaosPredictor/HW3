#ifndef MTM_ESCAPE_H_
#define MTM_ESCAPE_H_

#include <stdio.h> //TODO remove it
#include <stdlib.h>

#include "user.h"

typedef struct EscapeSystem_t EscapeSystem;



MtmErrorCode createSystem(EscapeSystem **sys);

MtmErrorCode destroySystem(EscapeSystem *sys);

MtmErrorCode createCompanySet(EscapeSystem* sys);




#endif /* MTM_ESCAPE_H_ */




