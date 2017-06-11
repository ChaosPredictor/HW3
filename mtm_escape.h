/*
 * mtm_escape.h
 *
 *  Created on: Jun 11, 2017
 *      Author: master
 */

#ifndef MTM_ESCAPE_H_
#define MTM_ESCAPE_H_

#include "system.h"
#include "common.h"


void lineReader(EscapeSystem sys, FILE* challenIn, FILE* challenOut, FILE* challenErr );



void addCompanyCase(EscapeSystem sys, FILE* challenErr);

void removeCompanyCase(EscapeSystem sys, FILE* challenErr);

void addRoomCase(EscapeSystem sys, FILE* challenErr);

void removeRoomCase(EscapeSystem sys, FILE* challenErr);

void addEscaperCase(EscapeSystem sys, FILE* challenErr);

void removeEscaperCase(EscapeSystem sys, FILE* challenErr);

void addAnOrderCase(EscapeSystem sys, FILE* challenErr);

void addRecommendedOrderCase(EscapeSystem sys, FILE* challenOut);

void reportDayCase(EscapeSystem sys, FILE* challenOut);

void reportBestCase(EscapeSystem sys, FILE* challenOut);

#endif /* MTM_ESCAPE_H_ */
