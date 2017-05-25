#include "test_utilities.h"
#include "../list_mtm/list_mtm1.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static ListElement copyString(ListElement str){
	assert(str);
	char* copy = malloc(strlen(str)+1);
	return copy != NULL ? strcpy(copy, str) : NULL;
}

static void freeString(ListElement str){
	free(str);
}

//static bool isLongerThan(ListElement element,ListFilterKey number) {
//	char* string = element;
//    return strlen(string) > *(int*)number;
//}

static bool testListCreate() {
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(copyString,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,freeString) == NULL);

	return true;
}

static bool testListCreateSuccess() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(list != NULL);
	ASSERT_TEST(listGetSize(list) == 0);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i = 0; i < 5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4])==0);

	listDestroy(list);
	return true;
}


static bool testListFilter() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	//int key = 5;
	//List filtered = listFilter(list,isLongerThan, &key);
	//TODO
	//ASSERT_TEST(listGetSize(filtered) == 1);
	//TODO
	//ASSERT_TEST(strcmp(listGetFirst(filtered),a[3])==0);
	listDestroy(list);
	//listDestroy(filtered);
	return true;
}
static bool testListCopy() {
	List list = listCreate(copyString,freeString);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	List newList = listCopy(list);
	ASSERT_TEST(listGetSize(newList) == 5);
	ASSERT_TEST(strcmp(listGetFirst(newList),a[4])==0);
	listDestroy(newList);
	listDestroy(list);
	return true;
}

static bool testListGetSize() {
	ASSERT_TEST(listGetSize(NULL) == -1);
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetSize(list) == 0);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	//TODO
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	return true;
}

static bool testListGetFirst() {
	ASSERT_TEST(listGetFirst(NULL) == NULL);
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetFirst(list) == NULL);
	//TODO Success case
	listDestroy(list);
	return true;
}

static bool testListGetNext() {
	return true;
}

static bool testListInsertFirst() {
	return true;
}

static bool testListInsertLast() {
	return true;
}

static bool testListInsertBeforeCurrent() {
	return true;
}

static bool testListInsertAfterCurrent() {
	return true;
}

static bool testListRemoveCurrent() {
	return true;
}

static bool testListSort() {
	return true;
}

static bool testListClear() {
	List list = listCreate(copyString,freeString);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listClear(list);
	ASSERT_TEST(listGetSize(list) == 0);
	listDestroy(list);
	return true;
}

static bool testListDestroy() {
	List list = listCreate(copyString,freeString);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(NULL);
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	return true;
}

int main (int argv, char** arc){
	RUN_TEST(testListCreate);
	RUN_TEST(testListFilter);
	RUN_TEST(testListCopy);
	RUN_TEST(testListGetSize);
	RUN_TEST(testListGetFirst);
	RUN_TEST(testListGetNext);
	RUN_TEST(testListInsertFirst);
	RUN_TEST(testListInsertLast);
	RUN_TEST(testListInsertBeforeCurrent);
	RUN_TEST(testListInsertAfterCurrent);
	RUN_TEST(testListRemoveCurrent);
	RUN_TEST(testListSort);
	RUN_TEST(testListClear);
	RUN_TEST(testListDestroy);

	RUN_TEST(testListCreateSuccess);
	return 0;
}
