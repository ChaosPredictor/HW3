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
#include "mtm_ex3.h"

typedef struct faculty_t{
	TechnionFaculty id;
	int income;
} *Faculty;


ListElement copyDay(ListElement faculty);

void freeDay(ListElement faculty);


List createFaculties(int numberOfFaculties);

MtmErrorCode addIncomeToFaculty(List Faculties, TechnionFaculty facultyNumber, int income);

int compareFacultyByIncomeAndId(ListElement listElement1, ListElement listElement2);

List returnBestNFaculties(List faculties, int number);

int returnTotalRevenue(List faculties);

#endif /* FACULTY_H_ */
