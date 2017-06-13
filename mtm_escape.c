/*
 * mtm_escape.c
 *
 *  Created on: Jun 11, 2017
 *      Author: master
 */


#include "mtm_escape.h"


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

	result = inputChannelSelector(argc, argv, &channelIn, &channelOut );
	if ( result != MTM_SUCCESS) {
		destroySystem(sys);
		mtmPrintErrorMessage(stderr, result);
		return -1;
	}

	result = lineReader(sys, channelIn, channelOut );
	if ( result != MTM_SUCCESS) {
		destroySystem(sys);
		mtmPrintErrorMessage(stderr, result);
		freeChannels(channelIn, channelOut );
		return -1;
	}

	destroySystem(sys);
	freeChannels(channelIn, channelOut );
	return 0;
}

void freeChannels(FILE* channelIn, FILE* channelOut ) {
	if ( channelIn != stdin) fclose(channelIn);
	if ( channelOut != stdout) fclose(channelOut);
}


MtmErrorCode lineReader(EscapeSystem sys, FILE* channelIn, FILE* channelOut ) {
	char line[MAX_LEN];
	MtmErrorCode result = MTM_SUCCESS;
	while ( fgets(line, MAX_LEN, channelIn) != NULL) {
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
			result = addCompanyCase(sys);

		} else if ( numberOfCommand == 2 ) {
			result = removeCompanyCase(sys);

		} else if ( numberOfCommand == 3 ) {
			result = addRoomCase(sys);

		} else if ( numberOfCommand == 4 ) {
			result = removeRoomCase(sys);

		} else if ( numberOfCommand == 5 ) {
			result = addEscaperCase(sys);

		} else if ( numberOfCommand == 6 ) {
			result = removeEscaperCase(sys);

		}  else if ( numberOfCommand == 7 ) {
			result = addAnOrderCase(sys);

		} else if ( numberOfCommand == 8 ) {
			result = addRecommendedOrderCase(sys);

		} else if ( numberOfCommand == 9 ) {
			result = reportDayCase(sys, channelOut);

		} else if ( numberOfCommand == 10 ) {
			result = reportBestCase(sys, channelOut);
		}
		if ( result == MTM_OUT_OF_MEMORY ) return result;
	}
	return MTM_SUCCESS;
}

MtmErrorCode addCompanyCase(EscapeSystem sys) {
	char* email = strtok(NULL, " \t");
	int faculty = atoi( strtok(NULL, " ") );
	MtmErrorCode result = addCompany(sys, email, faculty );
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode removeCompanyCase(EscapeSystem sys) {
	char* email = strtok(NULL, " \r\n");
	MtmErrorCode result = removeCompany(sys, email);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode addRoomCase(EscapeSystem sys) {
	char* email = strtok(NULL, " \t");
	int id = atoi( strtok(NULL, " ") );
	int price = atoi( strtok(NULL, " ") );
	int num_ppl = atoi( strtok(NULL, " ") );
	char* working_hrs = strtok(NULL, " \t");
	int difficulty = atoi( strtok(NULL, " ") );
	MtmErrorCode result = addARoom(sys, email, id, price, num_ppl, working_hrs, difficulty);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode removeRoomCase(EscapeSystem sys) {
	int faculty = atoi( strtok(NULL, " ") );
	int id = atoi( strtok(NULL, " ") );
	MtmErrorCode result = removeARoom(sys, faculty, id);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode addEscaperCase(EscapeSystem sys) {
	char* email = strtok(NULL, " \t");
	int faculty = atoi( strtok(NULL, " ") );
	int skill_level = atoi( strtok(NULL, " ") );
	MtmErrorCode result = addEscaper(sys, email, faculty, skill_level);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode removeEscaperCase(EscapeSystem sys) {
	char* email = strtok(NULL, " \r\n");
	MtmErrorCode result = removeEscaper(sys, email);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode addAnOrderCase(EscapeSystem sys) {
	char* email = strtok(NULL, " \t");
	int faculty = atoi( strtok(NULL, " ") );
	int id = atoi( strtok(NULL, " ") );
	char* time = strtok(NULL, " \t");
	int num_ppl = atoi( strtok(NULL, " ") );
	MtmErrorCode result = addAnOrder(sys, email, faculty, id, time, num_ppl);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode addRecommendedOrderCase(EscapeSystem sys) {
	char* email = strtok(NULL, " \t");
	int num_ppl = atoi( strtok(NULL, " ") );
	MtmErrorCode result = addRecommendedOrder(sys, email, num_ppl );
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode reportDayCase(EscapeSystem sys, FILE* channelOut) {
	MtmErrorCode result = reportDay(channelOut, sys);
	return result;
}

MtmErrorCode reportBestCase(EscapeSystem sys, FILE* channelOut) {
	MtmErrorCode result = reportBest(channelOut, sys);
	return result;
}





