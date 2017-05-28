/*
 * mtm_escape.c
 *
 *  Created on: May 27, 2017
 *      Author: master
 */

#include "mtm_escape.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENG 200


struct EscapeSystem_t
{
	int temp;
	Set *company;
};

int main(int argc, char *argv[]) {

	FILE *file = stdin;

	if ( !(argc == 1 || argc == 3 || argc == 5) ) {
		printf("‫‪MTM_INVALID_COMMAND_LINE_PARAMETERS.‬‬\n");
		//TODO change it to mtm_ex3 print function
		fclose(file);
		return -1;
	} else if ( argc == 5 ) {
		if ( strcmp(argv[1],"-i") == 0 ) {
			file = fopen(argv[2], "r");
		} else if ( strcmp(argv[3],"-i") == 0 ) {
			file = fopen(argv[4], "r");
		}
		if ( file == NULL ) {
			printf("MTM_CANNOT_OPEN_FILE.");
			//TODO change it to mtm_ex3 print function
			fclose(file);
			return -1;
		}

		//TODO output
	}

	char a[MAX_NAME_LENG];

	while ( fgets(a, MAX_NAME_LENG, file) != NULL) {

		const char* firstNonSpace = a;
		while(*firstNonSpace != '\0' && isspace(*firstNonSpace)) {
			++firstNonSpace;
		}
		size_t len = strlen(firstNonSpace)+1;
		memmove(a, firstNonSpace, len);
		//const char *firstChar[1] = &a[0];
		if ( strcmp(a,"") != 0 && a[0] != '#' ) {
			printf("your input a: %s", a);
		}

	}

	fclose(file);
}

MtmErrorCode create_system(EscapeSystem *sys) {

	return MTM_SUCCESS;
}
