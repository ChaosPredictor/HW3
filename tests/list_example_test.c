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

static bool isLongerThan(ListElement element, ListFilterKey number) {
	char* string = element;
    return strlen(string) > *(int*)number;
}

static int compareString(ListElement element1, ListElement element2) {
    return strcmp((char*)element1, (char*)element2);
}



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
	ASSERT_TEST(listGetCurrent(list) == NULL);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list),a[4]) == 0);
	listDestroy(list);
	return true;
}

static bool testListFilter() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	int key = 5;
	List filtered = listFilter(list,isLongerThan, &key);
	//printf("\nsize:%d\n", listGetSize(filtered));
	ASSERT_TEST(listGetSize(filtered) == 1);
	ASSERT_TEST(strcmp(listGetFirst(filtered),a[3])==0);
	listDestroy(list);
	listDestroy(filtered);
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
	//TODO iteration location
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
	ASSERT_TEST(listGetSize(list) == 5);
	listDestroy(list);
	return true;
}

static bool testListGetFirst() {
	ASSERT_TEST(listGetFirst(NULL) == NULL);
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetFirst(list) == NULL);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetCurrent(list) == NULL);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4])==0);
	ASSERT_TEST(strcmp(listGetCurrent(list),a[4])==0);
	listDestroy(list);
	return true;
}

static bool testListGetNext() {
	ASSERT_TEST(listGetNext(NULL) == NULL);
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetNext(list) == NULL);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i = 0 ; i < 5; ++i ){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST( listGetNext(list) == NULL);
	ASSERT_TEST(listGetCurrent(list) == NULL);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	for (int i = 4 ; i > 0; --i ){
		ASSERT_TEST(strcmp(listGetCurrent(list),a[i]) == 0);
		ASSERT_TEST(strcmp(listGetNext(list),a[i-1]) == 0);
	}
	ASSERT_TEST(listGetNext(list) == NULL);
	listDestroy(list);
	return true;
}

static bool testListInsertFirst() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetFirst(list) == NULL);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
		ASSERT_TEST(strcmp(listGetFirst(list),a[i])==0);
	}
	listDestroy(list);
	return true;
}

static bool testListInsertLast() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetFirst(list) == NULL);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	listInsertLast(list,a[0]);
	ASSERT_TEST(strcmp(listGetFirst(list),a[0])==0);
	for (int i = 1; i < 5; ++i ){
		listInsertLast(list,a[i]);
		ASSERT_TEST(strcmp(listGetFirst(list),a[i]) != 0);
	}
	listDestroy(list);
	return true;
}

static bool testListInsertBeforeCurrent() {
	List list = listCreate(copyString,freeString);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
	listInsertBeforeCurrent(list,"ccc");


	//ListPrint(list);
	char* b[6] = {"aaa","bbb","NI","ccc","hello mister fish","I"};
	ASSERT_TEST(strcmp(listGetFirst(list),b[5]) == 0);
	for (int i = 4; i >= 0; --i){
		//printf("\n%d\n",i);
		ASSERT_TEST(strcmp(listGetNext(list),b[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListInsertAfterCurrent() {
	List list = listCreate(copyString,freeString);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
	listInsertAfterCurrent(list,"ccc");


	char* b[6] = {"aaa","bbb","ccc","NI","hello mister fish","I"};
	ASSERT_TEST(strcmp(listGetFirst(list),b[5]) == 0);

	for (int i = 4; i >= 0; --i){
		ASSERT_TEST(strcmp(listGetNext(list),b[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListRemoveCurrent() {
	List list = listCreate(copyString,freeString);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
	//ListPrint(list);
	listRemoveCurrent(list);
	//ListPrint(list);

	char* b[6] = {"aaa","bbb","hello mister fish","I"};
	ASSERT_TEST(strcmp(listGetFirst(list),b[3]) == 0);

	for (int i = 2; i >= 0; --i){
		ASSERT_TEST(strcmp(listGetNext(list),b[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListSort() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	List list = listCreate(copyString,freeString);
	for (int i = 0; i < 5; ++i ){
		listInsertFirst(list,a[i]);
	}
	ListResult result = listSort(list, compareString);
	ASSERT_TEST(result == 0);
	char* b[5] = {"I","NI","aaa","bbb","hello mister fish"};
	ASSERT_TEST(strcmp(listGetFirst(list),b[0]) == 0);
	for (int i = 1; i < 5; ++i ){
		ASSERT_TEST(strcmp(listGetNext(list),b[i]) == 0);
	}
	listDestroy(list);
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
	//TODO test that is destroyed
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
