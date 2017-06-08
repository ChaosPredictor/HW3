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


ListElement copyFaculty(ListElement faculty);

void freeFaculty(ListElement faculty);

int compareFacultyByIncomeAndId(const ListElement listElement1, const ListElement listElement2);

MtmErrorCode addIncomeToFaculty(Faculty faculty, int income);






#endif /* FACULTY_H_ */
