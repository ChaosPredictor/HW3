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

/* copy faculty function
 * @param
 * 	faculty - a new faculty object that same to the original
 * @return
 *	faculty - copy of the faculty if success
 *	NULL - otherwise (memory leak)
 */
ListElement copyFaculty(ListElement faculty);

/* free faculty function
 * @param
 * 	faculty - a faculty to free
 */
void freeFaculty(ListElement faculty);

/* compare two faculties function
 * @param
 * 	faculty1 - first of the faculties to compare
 * 	faculty2 - second of the faculties to compare
 * @return
 * 	0 - faculty1 equal to faculty2 (email)
 * 	1 - faculty1 higher than faculty2 (email)
 * 	-1 - faculty2 higher than faculty1 (email)
 */
int compareFacultyByIncomeAndId(const ListElement list_element1, \
		const ListElement list_element2);

/* add income to faculty
 * @param
 * 	faculty - faculties to add income
 * 	income - income to add
 * @return
 *  MTM_SUCCESS
 */
MtmErrorCode addIncomeToFaculty(Faculty faculty, int income);






#endif /* FACULTY_H_ */
