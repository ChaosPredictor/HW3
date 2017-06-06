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

List createFaculties(int numberOfFaculties) {
	List faculties = listCreate(copyFaculty, freeFaculty);
	if ( faculties == NULL ) return NULL;

	Faculty newFaculty = malloc(sizeof(struct faculty_t));

	for( int i = 0; i < numberOfFaculties; i++) {
		newFaculty->id = i;
		newFaculty->income = 0;
		listInsertFirst(faculties, newFaculty);
	}
	free(newFaculty);
	return faculties;
}


MtmErrorCode addIncomeToFaculty(List Faculties, TechnionFaculty facultyNumber, int income) {
	Faculty faculty = listGetFirst(Faculties);
	while ( faculty != NULL ) {

		if ( faculty->id == facultyNumber ) {
			faculty->income += income;
			return MTM_SUCCESS;
		}
		faculty = listGetNext(Faculties);
	}
	return MTM_INVALID_PARAMETER;
}

int compareFacultyByIncomeAndId(ListElement listElement1, ListElement listElement2) {
	if ((((Faculty)listElement2)->income) > (((Faculty)listElement1)->income)) {
		return 1;
	} else if ((((Faculty)listElement2)->income) == (((Faculty)listElement1)->income)) {
		return ((((Faculty)listElement2)->id) - (((Faculty)listElement1)->id));
	} else {
		return -1;
	}
}

List returnBestNFaculties(List faculties, int number) {
	listSort(faculties, compareFacultyByIncomeAndId);
	//TODO check return;
	List newList = listCreate(copyFaculty, freeFaculty);
	ListElement faculty = listGetFirst( faculties );
	for(int i = 0; i < number; i++) {
		listInsertLast(newList, faculty);
		faculty = listGetNext( faculties );
	}
	return newList;
}

int returnTotalRevenue(List faculties) {
	Faculty faculty = listGetFirst(faculties);
	int result = 0;
	while ( faculty != NULL ) {
		result += faculty->income;
		faculty = listGetNext(faculties);
	}
	return result;
}



