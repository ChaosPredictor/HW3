/*
 * faculty.c
 *
 *  Created on: Jun 7, 2017
 *      Author: master
 */


#include "faculty.h"



ListElement copyFaculty(ListElement faculty) {
	if ( faculty == NULL ) return NULL;
	//TODO maybe assert
	Faculty newFaculty = malloc(sizeof(struct faculty_t));
	if( newFaculty == NULL ) return NULL;
	newFaculty->id = ((Faculty)faculty)->id;
	newFaculty->income = ((Faculty)faculty)->income;
	return newFaculty;
}

void freeFaculty(ListElement faculty) {
	if ( faculty == NULL ) return;
	free((Faculty)faculty);
}

int compareFacultyByIncomeAndId(const ListElement listElement1, const ListElement listElement2) {
	if ((((Faculty)listElement2)->income) > (((Faculty)listElement1)->income)) {
		return 1;
	} else if ((((Faculty)listElement2)->income) == (((Faculty)listElement1)->income)) {
		return ((((Faculty)listElement1)->id) - (((Faculty)listElement2)->id));
	} else {
		return -1;
	}
}

MtmErrorCode addIncomeToFaculty(Faculty faculty, int income) {
	faculty->income += income;
	return MTM_SUCCESS;
}


