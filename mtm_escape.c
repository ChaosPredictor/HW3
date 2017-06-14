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

	FILE *channel_in = NULL;
	FILE *channel_out = NULL;

	result = channelSelectorFunction(argc, argv, &channel_in, &channel_out );
	if ( result != MTM_SUCCESS) {
		destroySystem(sys);
		mtmPrintErrorMessage(stderr, result);
		return -1;
	}

	result = lineReader(sys, channel_in, channel_out );
	if ( result != MTM_SUCCESS) {
		destroySystem(sys);
		mtmPrintErrorMessage(stderr, result);
		freeChannels(channel_in, channel_out );
		return -1;
	}

	destroySystem(sys);
	freeChannels(channel_in, channel_out );
	return 0;
}

void freeChannels(FILE* channel_in, FILE* channel_out ) {
	if ( channel_in != stdin) fclose(channel_in);
	if ( channel_out != stdout) fclose(channel_out);
}


MtmErrorCode lineReader(EscapeSystem sys, FILE* channel_in, FILE* channel_out ) {
	char line[MAX_LEN];
	MtmErrorCode result = MTM_SUCCESS;
	while ( fgets(line, MAX_LEN, channel_in) != NULL) {
		const char* first_none_space = line;
		while(*first_none_space != '\0' && isspace(*first_none_space)) {
			++first_none_space;
		}
		size_t len = strlen(first_none_space)+1;
		memmove(line, first_none_space, len);

		int number_of_command = convertStringToCommand( line );
		strtok(line, " \t");
		strtok(NULL, " \t");
		if ( number_of_command == 1 ) {
			result = addCompanyCase(sys);

		} else if ( number_of_command == 2 ) {
			result = removeCompanyCase(sys);

		} else if ( number_of_command == 3 ) {
			result = addRoomCase(sys);

		} else if ( number_of_command == 4 ) {
			result = removeRoomCase(sys);

		} else if ( number_of_command == 5 ) {
			result = addEscaperCase(sys);

		} else if ( number_of_command == 6 ) {
			result = removeEscaperCase(sys);

		}  else if ( number_of_command == 7 ) {
			result = addAnOrderCase(sys);

		} else if ( number_of_command == 8 ) {
			result = addRecommendedOrderCase(sys);

		} else if ( number_of_command == 9 ) {
			result = reportDayCase(sys, channel_out);

		} else if ( number_of_command == 10 ) {
			result = reportBestCase(sys, channel_out);
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
	MtmErrorCode result = addRoom(sys, email, id, price, num_ppl, \
			working_hrs, difficulty);
	if ( result != MTM_SUCCESS ) {
		mtmPrintErrorMessage(stderr, result);
	}
	return result;
}

MtmErrorCode removeRoomCase(EscapeSystem sys) {
	int faculty = atoi( strtok(NULL, " ") );
	int id = atoi( strtok(NULL, " ") );
	MtmErrorCode result = removeRoom(sys, faculty, id);
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

MtmErrorCode reportDayCase(EscapeSystem sys, FILE* channel_out) {
	MtmErrorCode result = reportDay(channel_out, sys);
	return result;
}

MtmErrorCode reportBestCase(EscapeSystem sys, FILE* channel_out) {
	MtmErrorCode result = reportBest(channel_out, sys);
	return result;
}





