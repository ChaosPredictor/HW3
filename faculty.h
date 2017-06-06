/*
 * faculty.h
 *
 *  Created on: Jun 7, 2017
 *      Author: master
 */

#ifndef FACULTY_H_
#define FACULTY_H_

#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct faculty_t{
	TechnionFaculty id;
	int income;
} *Faculty;


ListElement copyDay(ListElement faculty);

void freeDay(ListElement faculty);


List createFaculties();

MtmErrorCode addIncomeToFaculty(List Faculties, TechnionFaculty facultyNumber, int income);

int compareFAcultyByIncomeAndId(ListElement listElement1, ListElement listElement2);

List returnBestNFaculties(List faculties, int number);

#endif /* FACULTY_H_ */
