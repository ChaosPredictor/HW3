/*
 * mtm_escape.c
 *
 *  Created on: May 27, 2017
 *      Author: master
 */

#include "mtm_escape.h"
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENG 200

int main(int argc, char *argv[]) {

	FILE *file = stdin;

	if ( !(argc == 1 || argc == 3 || argc == 5) ) {
		printf("‫‪MTM_INVALID_COMMAND_LINE_PARAMETERS.‬‬\n");
		//TODO change it to mtm_ex3 print function
		return -1;
	} else if ( argc == 5 ) {
		if ( strcmp(argv[1],"-i") == 0 ) {
			file = fopen(argv[2], "r");
		} else if ( strcmp(argv[3],"-i") == 0 ) {
			file = fopen(argv[4], "r");
		}

	}



	char a[MAX_NAME_LENG];


	//while ( fscanf(file,"%50s[^\n]%c", a, b)  != EOF ) {
	//while ( fgets(a, MAX_NAME_LENG, stdin) != NULL) {

	while ( fgets(a, MAX_NAME_LENG, file) != NULL) {
		printf("your input a: %s", a);
		//printf("your input b: %s\n", b);
		//printf("your input c: %s\n", c);
	}
}
