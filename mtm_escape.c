/*
 * mtm_escape.c
 *
 *  Created on: Jun 11, 2017
 *      Author: master
 */


#include "system.h"


#define MAX_LINE_LENG 300


int main(int argc, char *argv[]) {
	MtmErrorCode result;

	EscapeSystem system = malloc(sizeof(struct EscapeSystem_t));
	if ( system == NULL ) {
		mtmPrintErrorMessage(stdout, MTM_OUT_OF_MEMORY);
		return -1;
	}
	result = createSystem(system);
	if ( result != MTM_SUCCESS) {
		mtmPrintErrorMessage(stdout, result);
		free(system);
		return -1;
	}

	FILE *challenIn = NULL;
	FILE *challenOut = NULL;

	result = inputChannelSelector(argc, argv, &challenIn, &challenOut );
	if ( result != MTM_SUCCESS) {
		destroySystem(system);
		mtmPrintErrorMessage(stdout, MTM_INVALID_COMMAND_LINE_PARAMETERS);
		return -1;
	}

	char line[MAX_LINE_LENG];

	while ( fgets(line, MAX_LINE_LENG, challenIn) != NULL) {

		const char* firstNonSpace = line;
		while(*firstNonSpace != '\0' && isspace(*firstNonSpace)) {
			++firstNonSpace;
		}
		size_t len = strlen(firstNonSpace)+1;
		memmove(line, firstNonSpace, len);

		int numberOfCommand = convertStringToCommand( line );
		strtok(line, " \t");
		strtok(NULL, " \t");

		if ( numberOfCommand == 1 ) {
			char* email = strtok(NULL, " ");
			int faculty = atoi( strtok(NULL, " ") );
			//TODO check return value
			addCompany(system, email, faculty );
		} else if ( numberOfCommand == 2 ) {
			char* email = strtok(NULL, " ");
			//TODO check return value
			removeCompany(system, email);
		} else if ( numberOfCommand == 3 ) {
			char* email = strtok(NULL, " ");
			int id = atoi( strtok(NULL, " ") );
			int price = atoi( strtok(NULL, " ") );
			int num_ppl = atoi( strtok(NULL, " ") );
			char* working_hrs = strtok(NULL, " ");
			int difficulty = atoi( strtok(NULL, " ") );
			//TODO check return value
			addARoom(system, email, id, price, num_ppl, working_hrs, difficulty);
		} else if ( numberOfCommand == 4 ) {
			int faculty = atoi( strtok(NULL, " ") );
			int id = atoi( strtok(NULL, " ") );
			//TODO check return value
			removeARoom(system, faculty, id);
		} else if ( numberOfCommand == 5 ) {
			char* email = strtok(NULL, " ");
			int faculty = atoi( strtok(NULL, " ") );
			int skill_level = atoi( strtok(NULL, " ") );
			//TODO check return value
			addAnEscaper(system, email, faculty, skill_level);
		} else if ( numberOfCommand == 6 ) {
			char* email = strtok(NULL, " \n");
			//TODO check return value
			removeAnEscaper(system, email);
		}  else if ( numberOfCommand == 7 ) {
			char* email = strtok(NULL, " ");
			int faculty = atoi( strtok(NULL, " ") );
			int id = atoi( strtok(NULL, " ") );
			char* time = strtok(NULL, " ");
			int num_ppl = atoi( strtok(NULL, " ") );
			//TODO check return value
			addAnOrder(system, email, faculty, id, time, num_ppl);
		} else if ( numberOfCommand == 8 ) {
			char* email = strtok(NULL, " ");
			int num_ppl = atoi( strtok(NULL, " ") );
			//TODO check return value
			addRecommendedOrder(system, email, num_ppl );
		} else if ( numberOfCommand == 9 ) {
			//TODO check return value
			reportDay(challenOut, system);
		} else if ( numberOfCommand == 10 ) {
			//TODO check return value
			reportBest(challenOut, system);
		}

	}
	//TODO check return value
	destroySystem(system);

	if ( challenIn != stdin) fclose(challenIn);
	if ( challenOut != stdin) fclose(challenOut);


	return 0;
}
