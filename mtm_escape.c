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
		mtmPrintErrorMessage(stderr, MTM_OUT_OF_MEMORY);
		return -1;
	}
	result = createSystem(sys);
	if ( result != MTM_SUCCESS) {
		mtmPrintErrorMessage(stderr, result);
		free(sys);
		return -1;
	}

	FILE *channelIn = NULL;
	FILE *channelOut = NULL;
	FILE *channelErr = NULL;

	result = inputChannelSelector(argc, argv, &channelIn, &channelOut, &channelErr );
	if ( result != MTM_SUCCESS) {
		destroySystem(sys);
		mtmPrintErrorMessage(stderr, result);
		freeChannels(channelIn, channelOut , channelErr);
		return -1;
	}

	result = lineReader(sys, channelIn, channelOut, channelErr );
	if ( result != MTM_SUCCESS) {
		destroySystem(sys);
		mtmPrintErrorMessage(stderr, result);
		freeChannels(channelIn, channelOut , channelErr);
		return -1;
	}

	destroySystem(sys);
	freeChannels(channelIn, channelOut , channelErr);
	return 0;
}

void freeChannels(FILE* channelIn, FILE* channelOut , FILE* channelErr) {
	if ( channelIn != stdin) fclose(channelIn);
	if ( channelOut != stdout) fclose(channelOut);
	if ( channelErr != stderr) fclose(channelErr);
}


MtmErrorCode lineReader(EscapeSystem sys, FILE* channelIn, FILE* channelOut , FILE* channelErr) {
	char line[MAX_LINE_LENG];
	MtmErrorCode result;
	while ( fgets(line, MAX_LINE_LENG, channelIn) != NULL) {

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
			result = addCompanyCase(sys, channelErr);
		} else if ( numberOfCommand == 2 ) {
			result = removeCompanyCase(sys, channelErr);
		} else if ( numberOfCommand == 3 ) {
			result = addRoomCase(sys, channelErr);
		} else if ( numberOfCommand == 4 ) {
			result = removeRoomCase(sys, channelErr);
		} else if ( numberOfCommand == 5 ) {
			result = addEscaperCase(sys, channelErr);
		} else if ( numberOfCommand == 6 ) {
			result = removeEscaperCase(sys, channelErr);
		}  else if ( numberOfCommand == 7 ) {
			result = addAnOrderCase(sys, channelErr);
		} else if ( numberOfCommand == 8 ) {
			result = addRecommendedOrderCase(sys, channelErr);
		} else if ( numberOfCommand == 9 ) {
			result = reportDayCase(sys, channelOut);
		} else if ( numberOfCommand == 10 ) {
			result = reportBestCase(sys, channelOut);
		}
		if ( result == MTM_OUT_OF_MEMORY ) return result;
	}
	return MTM_SUCCESS;
}

MtmErrorCode addCompanyCase(EscapeSystem sys, FILE* channelErr) {
	char* email = strtok(NULL, " ");
	int faculty = atoi( strtok(NULL, " ") );
	MtmErrorCode result = addCompany(sys, email, faculty );
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(channelErr, result);
	}
	return result;
}

MtmErrorCode removeCompanyCase(EscapeSystem sys, FILE* channelErr) {
	char* email = strtok(NULL, " ");
	//TODO check return value
	MtmErrorCode result = removeCompany(sys, email);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(channelErr, result);
	}
	return result;
}

MtmErrorCode addRoomCase(EscapeSystem sys, FILE* channelErr) {
	char* email = strtok(NULL, " ");
	int id = atoi( strtok(NULL, " ") );
	int price = atoi( strtok(NULL, " ") );
	int num_ppl = atoi( strtok(NULL, " ") );
	char* working_hrs = strtok(NULL, " ");
	int difficulty = atoi( strtok(NULL, " ") );
	//TODO check return value
	MtmErrorCode result = addARoom(sys, email, id, price, num_ppl, working_hrs, difficulty);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(channelErr, result);
	}
	return result;
}

MtmErrorCode removeRoomCase(EscapeSystem sys, FILE* channelErr) {
	int faculty = atoi( strtok(NULL, " ") );
	int id = atoi( strtok(NULL, " ") );
	//TODO check return value
	MtmErrorCode result = removeARoom(sys, faculty, id);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(channelErr, result);
	}
	return result;
}

MtmErrorCode addEscaperCase(EscapeSystem sys, FILE* channelErr) {
	char* email = strtok(NULL, " ");
	int faculty = atoi( strtok(NULL, " ") );
	int skill_level = atoi( strtok(NULL, " ") );
	//TODO check return value
	MtmErrorCode result = addAnEscaper(sys, email, faculty, skill_level);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(channelErr, result);
	}
	return result;
}

MtmErrorCode removeEscaperCase(EscapeSystem sys, FILE* channelErr) {
	char* email = strtok(NULL, " \n");
	//TODO check return value
	MtmErrorCode result = removeAnEscaper(sys, email);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(channelErr, result);
	}
	return result;
}

MtmErrorCode addAnOrderCase(EscapeSystem sys, FILE* channelErr) {
	char* email = strtok(NULL, " ");
	int faculty = atoi( strtok(NULL, " ") );
	int id = atoi( strtok(NULL, " ") );
	char* time = strtok(NULL, " ");
	int num_ppl = atoi( strtok(NULL, " ") );
	//TODO check return value
	MtmErrorCode result = addAnOrder(sys, email, faculty, id, time, num_ppl);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(channelErr, result);
	}
	return result;
}

MtmErrorCode addRecommendedOrderCase(EscapeSystem sys, FILE* channelErr) {
	char* email = strtok(NULL, " ");
	int num_ppl = atoi( strtok(NULL, " ") );
	//TODO check return value
	MtmErrorCode result = addRecommendedOrder(sys, email, num_ppl );
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(channelErr, result);
	}
	return result;
}

MtmErrorCode reportDayCase(EscapeSystem sys, FILE* channelOut) {
	//TODO check return value
	reportDay(channelOut, sys);
	return MTM_SUCCESS;
}

MtmErrorCode reportBestCase(EscapeSystem sys, FILE* channelOut) {
	//TODO check return value
	reportBest(channelOut, sys);
	return MTM_SUCCESS;
}





