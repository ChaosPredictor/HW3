/*
 * faculty.c
 *
 *  Created on: Jun 7, 2017
 *      Author: master
 */


#include "faculty.h"



ListElement copyFaculty(ListElement faculty) {
	if ( faculty == NULL ) return NULL;
	Faculty new_faculty = malloc(sizeof(struct faculty_t));
	if( new_faculty == NULL ) return NULL;
	new_faculty->id = ((Faculty)faculty)->id;
	new_faculty->income = ((Faculty)faculty)->income;
	return new_faculty;
}

void freeFaculty(ListElement faculty) {
	if ( faculty == NULL ) return;
	free((Faculty)faculty);
}

int compareFacultyByIncomeAndId(const ListElement list_element1, \
		const ListElement list_element2) {
	if ((((Faculty)list_element2)->income)>(((Faculty)list_element1)->income)){
		return 1;
	} else if ((((Faculty)list_element2)->income) == \
			(((Faculty)list_element1)->income)) {
		return ((((Faculty)list_element1)->id)-(((Faculty)list_element2)->id));
	} else {
		return -1;
	}
}

MtmErrorCode addIncomeToFaculty(Faculty faculty, int income) {
	faculty->income += income;
	return MTM_SUCCESS;
}


