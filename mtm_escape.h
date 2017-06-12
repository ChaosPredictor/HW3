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


MtmErrorCode lineReader(EscapeSystem sys, FILE* channelIn, FILE* channelOut, FILE* channelErr );

void freeChannels(FILE* channelIn, FILE* channelOut , FILE* channelErr);

MtmErrorCode addCompanyCase(EscapeSystem sys, FILE* channelErr);

MtmErrorCode removeCompanyCase(EscapeSystem sys, FILE* channelErr);

MtmErrorCode addRoomCase(EscapeSystem sys, FILE* channelErr);

MtmErrorCode removeRoomCase(EscapeSystem sys, FILE* channelErr);

MtmErrorCode addEscaperCase(EscapeSystem sys, FILE* channelErr);

MtmErrorCode removeEscaperCase(EscapeSystem sys, FILE* channelErr);

MtmErrorCode addAnOrderCase(EscapeSystem sys, FILE* channelErr);

MtmErrorCode addRecommendedOrderCase(EscapeSystem sys, FILE* channelOut);

MtmErrorCode reportDayCase(EscapeSystem sys, FILE* channelOut);

MtmErrorCode reportBestCase(EscapeSystem sys, FILE* channelOut);

#endif /* MTM_ESCAPE_H_ */
