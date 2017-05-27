/*
 * mtm_escape.c
 *
 *  Created on: May 27, 2017
 *      Author: master
 */

#include "mtm_escape.h"
#include <stdio.h>

#define MAX_NAME_LENG 200

int main() {

	//FILE *file = fopen("temp.txt", "r");
	char a[MAX_NAME_LENG];
	//char b[MAX_NAME_LENG];
	//char c[MAX_NAME_LENG];
	FILE *file = stdin;


	//while ( fscanf(file,"%50s[^\n]%c", a, b)  != EOF ) {
	//while ( fgets(a, MAX_NAME_LENG, stdin) != NULL) {

	while ( fgets(a, MAX_NAME_LENG, file) != NULL) {
		printf("your input a: %s", a);
		//printf("your input b: %s\n", b);
		//printf("your input c: %s\n", c);
	}
}
