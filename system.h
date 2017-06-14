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



/* Create System
 * create escapers, companies, rooms, faculties Sets
 * and
 * days Lists
 * @param
 * 	system - system the main object
 * @return
 *  MTM_NULL_PARAMETER - if system equal to  MULL
 *  MTM_OUT_OF_MEMORY - if one of the initialization fail
 *  MTM_SUCCESS - if all initialized
 */
MtmErrorCode createSystem(EscapeSystem system);


/* Destroy System
 * destroy escapers, companies, rooms, faculties Sets
 * and
 * days Lists
 * @param
 * 	system - system the main object
 * @return
 *  MTM_NULL_PARAMETER - if system equal to  MULL
 *  MTM_SUCCESS - if all destroyed
 */
MtmErrorCode destroySystem(EscapeSystem system);

/* Check if the is 1,3,5 or other number or arguments
 * and run the correct function
 * @param
 * 	argc - number of arguments
 * 	argv - value of each argument
 * 	channel_in - pointer to FILE* ( channel in)
 * 	channel_out - pointer to FILE* ( channel out)
 * @retunr
 *  MTM_INVALID_COMMAND_LINE_PARAMETERS - invalid command line parameters
 *  MTM_SUCCESS - channel_in & channel_out get rights values
 */
MtmErrorCode channelSelectorFunction(int argc, char* argv[], FILE** channel_in, \
		FILE** channel_out );

/* dealing with 5 input arguments case
 * initialize input AND output channels
 * and run the correct function
 * @param
 * 	argv - value of each argument
 * 	channel_in - pointer to FILE* ( channel in)
 * 	channel_out - pointer to FILE* ( channel out)
 * @retunr
 *  MTM_INVALID_COMMAND_LINE_PARAMETERS - invalid command line parameters
 *  MTM_CANNOT_OPEN_FILE - if can't open input or output file
 *  MTM_SUCCESS - channel_in & channel_out get rights values
 */
MtmErrorCode readBothFiles(char* argv[], FILE** channel_in, FILE** channel_out);

/* dealing with 3 input arguments case
 *  initialize input OR output channels
 * and run the correct function
 * @param
 * 	argv - value of each argument
 * 	channel_in - pointer to FILE* ( channel in)
 * 	channel_out - pointer to FILE* ( channel out)
 * @retunr
 *  MTM_INVALID_COMMAND_LINE_PARAMETERS - invalid command line parameters
 *  MTM_CANNOT_OPEN_FILE - if can't open input or output file
 *  MTM_SUCCESS - channel_in & channel_out get rights values
 */
MtmErrorCode readOneOfTheFiles(char* argv[],FILE** channel_in,FILE** channel_out);

/* Adding company to the system
 * @param
 * 	system - system the main object
 * 	email - email of the company
 * 	faculty - faculty of the company
 * @return
 * 	MTM_OUT_OF_MEMORY - if an allocation failed
 *  MTM_INVALID_PARAMETER - one of the parameters invalid
 *  MTM_EMAIL_ALREADY_EXISTS - if the email already exits in the system
 *  MTM_SUCCESS - if new company added
 */
MtmErrorCode addCompany(EscapeSystem system, const char* email, \
		TechnionFaculty faculty);

/* Removing company from the system
 * @param
 * 	system - system the main object
 * 	email - email of the company
 * @return
 * 	MTM_COMPANY_EMAIL_DOES_NOT_EXIST; - company email does not exits
 *  MTM_INVALID_PARAMETER - one of the parameters invalid
 *  MTM_RESERVATION_EXISTS - if the company have resevation (can't be removed)
 *  MTM_SUCCESS - if company removed
 */
MtmErrorCode removeCompany(EscapeSystem system, const char* email);


/* Find company in the system by email
 * @param
 * 	system - system the main object
 * 	email - email of the company
 * @return
 *  NULL -one of the parameters invalid or company does not exist in the system
 *  Company - company with the email
 */
Company findCompanyByEmail(const EscapeSystem system, const char* email);

/* check if company have ordered rooms
 * @param
 * 	system - system the main object
 * 	email - email of the company
 * @return
 *  true - if the is at least one order to one or more of the company rooms
 *  false - otherwise
 */
bool isAnyRoomOfACompanyOrdered(const EscapeSystem system, const char* email);


/* Adding escaper to the system
 * @param
 * 	system - system the main object
 * 	email - email of the escaper
 * 	faculty - faculty of the company
 *  skill_level - skill level of the escaper
 * @return
 * 	MTM_OUT_OF_MEMORY - if an allocation failed
 *  MTM_INVALID_PARAMETER - one of the parameters invalid
 *  MTM_EMAIL_ALREADY_EXISTS - if the email already exits in the system
 *  MTM_SUCCESS - if escaper added
 */
MtmErrorCode addEscaper(EscapeSystem system, const char* email, \
		TechnionFaculty faculty, SkillLevel skill_level);

/* Removing escaper from the system
 * @param
 * 	system - system the main object
 * 	email - email of the company
 * @return
 * 	MTM_CLIENT_EMAIL_DOES_NOT_EXIST; - escaper email does not exits
 *  MTM_INVALID_PARAMETER - one of the parameters invalid
 *  MTM_SUCCESS - if company removed
 */
MtmErrorCode removeEscaper(EscapeSystem system, const char* email);

/* Find escaper in the system by email
 * @param
 * 	system - system the main object
 * 	email - email of the company
 * @return
 *  NULL -one of the parameters invalid or escaper does not exist in the system
 *  escaper - escaper with the email
 */
Escaper findEscaperByEmail(const EscapeSystem system, const char* email );

/* check is escaper not occupied
 * @param
 * 	system - system the main object
 * 	days_from_today - when (which from to day0
 * 	hour - when (which hour)
 * 	escaper - escaper the check
 * @return
 * 	true - escaper free
 * 	false - otherwise
 */
bool isEscaperAvailable(const EscapeSystem system, int days_from_today, int hour, \
		SetElement escaper);

/* Adding room to the system
 * @param
 * 	system - system the main object
 * 	email - email of the company
 * 	id - id in the faculty of the company
 * 	price - price of the room per escaper
 * 	num_ppl - recommended number of people
 *  difficulty - recommended skill level of the room
 * @return
 * 	MTM_OUT_OF_MEMORY - if an allocation failed
 *  MTM_INVALID_PARAMETER - one of the parameters invalid
 *  MTM_COMPANY_EMAIL_DOES_NOT_EXIST - if not company the the email param
 *  MTM_ID_ALREADY_EXIST - there is room with this id in the faculty of the room
 *  MTM_SUCCESS - if room added
 */
MtmErrorCode addRoom(EscapeSystem system, const char* email, int id, int price, \
		int num_ppl, char* working_hrs, int difficulty);

/* Removing a room from the system
 * @param
 * 	system - system the main object
 * 	faculty - faculty of the room
 * 	id - id in the faculty of the company
 * @return
 * 	MTM_ID_DOES_NOT_EXIST - no room with this faculty & id
 *  MTM_INVALID_PARAMETER - one of the parameters invalid
 *  MTM_RESERVATION_EXISTS - if the company have reservation (can't be removed)
 *  MTM_SUCCESS - if company removed
 */
MtmErrorCode removeRoom(EscapeSystem system, TechnionFaculty faculty, int id);

/* Removing all rooms from the system
 * @param
 * 	system - system the main object
 * 	email - email of the company
 * @return
 * 	MTM_ID_DOES_NOT_EXIST - no room with this faculty & id
 *  MTM_INVALID_PARAMETER - one of the parameters invalid
 *  MTM_RESERVATION_EXISTS - if the company have reservation (can't be removed)
 *  MTM_SUCCESS - if company removed
 */
MtmErrorCode removeAllRoomsOfCompany(EscapeSystem system,\
		const char* company_email);


SetElement findRoom(const EscapeSystem system, TechnionFaculty faculty, int id);

Room findRecommendedRoom(const EscapeSystem system, const Escaper escaper, \
		int  num_ppl);

bool isRoomAvailable(const EscapeSystem system, int daysFromToday, int hour, \
		ListElement room);

Set findTheMostFitRooms(const Set rooms, \
		RecommendSetElement recommendSetElement, SetKey key1, SetKey key2 );



MtmErrorCode addAnOrder(EscapeSystem system, const char* email, \
		TechnionFaculty faculty, int id, const char* time, int num_ppl);

MtmErrorCode addRecommendedOrder(EscapeSystem system, char* email, int num_ppl);

MtmErrorCode addFirstAvailableOrder(EscapeSystem system, Order order, \
		SetElement room, SetElement escaper );

bool IsARoomOrdered(const EscapeSystem system, TechnionFaculty faculty, int id);

Day returnDayFromToday(const EscapeSystem system, int daysFromToday);

MtmErrorCode removedOrdersOfEscaper(EscapeSystem system, const char* email );


List createFaculties(int numberOfFaculties);

Faculty findFacultyByNumber(List Faculties, TechnionFaculty facultyNumber);

List returnListOfBestNFaculties(List faculties, int number);

int returnTotalFacultiesRevenue(List faculties);


MtmErrorCode reportDay(FILE* outputChannel, EscapeSystem systemtem);

MtmErrorCode reportBest(FILE* outputChannel, EscapeSystem systemtem);




#endif /* SYSTEM_H_ */
