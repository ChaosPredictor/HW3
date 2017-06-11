/*
 * mtm_escape.c
 *
 *  Created on: Jun 11, 2017
 *      Author: master
 */


#include "mtm_escape.h"


#define MAX_LINE_LENG 300


int main(int argc, char *argv[]) {
	MtmErrorCode result;

	EscapeSystem sys = malloc(sizeof(struct EscapeSystem_t));
	if ( sys == NULL ) {
		mtmPrintErrorMessage(stdout, MTM_OUT_OF_MEMORY);
		return -1;
	}
	result = createSystem(sys);
	if ( result != MTM_SUCCESS) {
		mtmPrintErrorMessage(stdout, result);
		free(sys);
		return -1;
	}

	FILE *challenIn = NULL;
	FILE *challenOut = NULL;
	FILE *challenErr = NULL;

	result = inputChannelSelector(argc, argv, &challenIn, &challenOut, &challenErr );
	if ( result != MTM_SUCCESS) {
		destroySystem(sys);
		mtmPrintErrorMessage(stdout, MTM_INVALID_COMMAND_LINE_PARAMETERS);
		return -1;
	}

	lineReader(sys, challenIn, challenOut, challenErr );
	//TODO check return value
	destroySystem(sys);

	if ( challenIn != stdin) fclose(challenIn);
	if ( challenOut != stdin) fclose(challenOut);


	return 0;
}

void lineReader(EscapeSystem sys, FILE* challenIn, FILE* challenOut , FILE* challenErr) {
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
			addCompanyCase(sys, challenErr);
		} else if ( numberOfCommand == 2 ) {
			removeCompanyCase(sys, challenErr);
		} else if ( numberOfCommand == 3 ) {
			addRoomCase(sys, challenErr);
		} else if ( numberOfCommand == 4 ) {
			removeRoomCase(sys, challenErr);
		} else if ( numberOfCommand == 5 ) {
			addEscaperCase(sys, challenErr);
		} else if ( numberOfCommand == 6 ) {
			removeEscaperCase(sys, challenErr);
		}  else if ( numberOfCommand == 7 ) {
			addAnOrderCase(sys, challenErr);
		} else if ( numberOfCommand == 8 ) {
			addRecommendedOrderCase(sys, challenErr);
		} else if ( numberOfCommand == 9 ) {
			reportDayCase(sys, challenOut);
		} else if ( numberOfCommand == 10 ) {
			reportBestCase(sys, challenOut);
		}

	}
}

void addCompanyCase(EscapeSystem sys, FILE* challenErr) {
	char* email = strtok(NULL, " ");
	int faculty = atoi( strtok(NULL, " ") );
	//TODO check return value
	addCompany(sys, email, faculty );
	return;
}

void removeCompanyCase(EscapeSystem sys, FILE* challenErr) {
	char* email = strtok(NULL, " ");
	//TODO check return value
	removeCompany(sys, email);
	return;
}

void addRoomCase(EscapeSystem sys, FILE* challenErr) {
	char* email = strtok(NULL, " ");
	int id = atoi( strtok(NULL, " ") );
	int price = atoi( strtok(NULL, " ") );
	int num_ppl = atoi( strtok(NULL, " ") );
	char* working_hrs = strtok(NULL, " ");
	int difficulty = atoi( strtok(NULL, " ") );
	//TODO check return value
	addARoom(sys, email, id, price, num_ppl, working_hrs, difficulty);
	return;
}

void removeRoomCase(EscapeSystem sys, FILE* challenErr) {
	int faculty = atoi( strtok(NULL, " ") );
	int id = atoi( strtok(NULL, " ") );
	//TODO check return value
	removeARoom(sys, faculty, id);
}

void addEscaperCase(EscapeSystem sys, FILE* challenErr) {
	char* email = strtok(NULL, " ");
	int faculty = atoi( strtok(NULL, " ") );
	int skill_level = atoi( strtok(NULL, " ") );
	//TODO check return value
	addAnEscaper(sys, email, faculty, skill_level);
}

void removeEscaperCase(EscapeSystem sys, FILE* challenErr) {
	char* email = strtok(NULL, " \n");
	//TODO check return value
	removeAnEscaper(sys, email);

}

void addAnOrderCase(EscapeSystem sys, FILE* challenErr) {
	char* email = strtok(NULL, " ");
	int faculty = atoi( strtok(NULL, " ") );
	int id = atoi( strtok(NULL, " ") );
	char* time = strtok(NULL, " ");
	int num_ppl = atoi( strtok(NULL, " ") );
	//TODO check return value
	addAnOrder(sys, email, faculty, id, time, num_ppl);
}

void addRecommendedOrderCase(EscapeSystem sys, FILE* challenErr) {
	char* email = strtok(NULL, " ");
	int num_ppl = atoi( strtok(NULL, " ") );
	//TODO check return value
	addRecommendedOrder(sys, email, num_ppl );
}

void reportDayCase(EscapeSystem sys, FILE* challenOut) {
	//TODO check return value
	reportDay(challenOut, sys);
}

void reportBestCase(EscapeSystem sys, FILE* challenOut) {
	//TODO check return value
	reportBest(challenOut, sys);
}





