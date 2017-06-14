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

/* read line by line from channel in running the match command and \
 * sending messages to channel out
 * @param
 * 	system  - the main object of the system
 * 	channel_in - the channel from which the function taking input\
 * 	 (stdin or file)
 * 	channel_out - the channel to which the function sending output\
 * 	 (strout or file)
 * @return
 *	faculty - copy of the faculty if success
 *	NULL - otherwise (memory leak)
 */
MtmErrorCode lineReaderFunction(EscapeSystem sys, FILE* channel_in, \
		FILE* channel_out );

/* close channel out/in if it's file
 * @param
 * 	channel_in - the channel from which the function taking input\
 * 	 (stdin or file)
 * 	channel_out - the channel to which the function sending output\
 * 	 (strout or file)
 */
void freeChannels(FILE* channelIn, FILE* channelOut );

/* running add company function
 * @param
 * 	system - the main object of the system
 * @return
 *  all addCompany function (from system) return values
 */
MtmErrorCode addCompanyCase(EscapeSystem sys);

/* running remove company function
 * @param
 * 	system - the main object of the system
 * @return
 *  all removeCompany function (from system) return values
 */
MtmErrorCode removeCompanyCase(EscapeSystem sys);

/* running add room function
 * @param
 * 	system - the main object of the system
 * @return
 *  all addRoom function (from system) return values
 */
MtmErrorCode addRoomCase(EscapeSystem sys);

/* running remove room function
 * @param
 * 	system - the main object of the system
 * @return
 *  all removeRoom function (from system) return values
 */
MtmErrorCode removeRoomCase(EscapeSystem sys);

/* running add escaper function
 * @param
 * 	system - the main object of the system
 * @return
 *  all addEscaper function (from system) return values
 */
MtmErrorCode addEscaperCase(EscapeSystem sys);

/* running remove escaper function
 * @param
 * 	system - the main object of the system
 * @return
 *  all remopveEscaper function (from system) return values
 */
MtmErrorCode removeEscaperCase(EscapeSystem sys);

/* running remove escaper function
 * @param
 * 	system - the main object of the system
 * @return
 *  all remopveEscaper function (from system) return values
 */
MtmErrorCode addOrderCase(EscapeSystem sys);

/* running recommended order function
 * @param
 * 	system - the main object of the system
 * @return
 *  all addRecommendedOrder function (from system) return values
 */
MtmErrorCode addRecommendedOrderCase(EscapeSystem sys);

/* running daily report function
 * @param
 * 	system - the main object of the system
 * 	channel_our - channel to print the report
 * @return
 *  all reportDay function (from system) return values
 */
MtmErrorCode reportDayCase(EscapeSystem sys, FILE* channel_out);

/* running report best function
 * @param
 * 	system - the main object of the system
 * 	channel_our - channel to print the report
 * @return
 *  all reportBest function (from system) return values
 */
MtmErrorCode reportBestCase(EscapeSystem sys, FILE* channel_out);

#endif /* MTM_ESCAPE_H_ */
