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


MtmErrorCode lineReader(EscapeSystem sys, FILE* channelIn, FILE* channelOut );

void freeChannels(FILE* channelIn, FILE* channelOut );

MtmErrorCode addCompanyCase(EscapeSystem sys);

MtmErrorCode removeCompanyCase(EscapeSystem sys);

MtmErrorCode addRoomCase(EscapeSystem sys);

MtmErrorCode removeRoomCase(EscapeSystem sys);

MtmErrorCode addEscaperCase(EscapeSystem sys);

MtmErrorCode removeEscaperCase(EscapeSystem sys);

MtmErrorCode addAnOrderCase(EscapeSystem sys);

MtmErrorCode addRecommendedOrderCase(EscapeSystem sys);

MtmErrorCode reportDayCase(EscapeSystem sys, FILE* channelOut);

MtmErrorCode reportBestCase(EscapeSystem sys, FILE* channelOut);

#endif /* MTM_ESCAPE_H_ */
