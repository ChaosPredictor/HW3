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

static int compareLexiStringLexicographical(ListElement element1, ListElement element2) {
    return strcmp((char*)element1, (char*)element2);
}

static int compareStringLength(ListElement element1, ListElement element2) {
    return strlen((char*)element1) - strlen((char*)element2);
}


static bool testListCreate() {
	ASSERT_TEST(listCreate(NULL,NULL) == NULL);
	ASSERT_TEST(listCreate(copyString,NULL) == NULL);
	ASSERT_TEST(listCreate(NULL,freeString) == NULL);

	return true;
}

static bool testListCreateSuccess() {
	List list = listCreate(copyString,freeString);
	ASSERT_TEST(list != NULL);
	ASSERT_TEST(listGetCurrent(list) == NULL);
	ASSERT_TEST(listGetSize(list) == 0);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i = 0; i < 5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(listGetCurrent(list) == NULL);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list),a[4]) == 0);
	for ( int i = 3; i > 0; --i ){
		ASSERT_TEST( strcmp(listGetNext(list),a[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListFilter() {
	List list = listCreate(copyString, freeString);

	ASSERT_TEST(listFilter(NULL, NULL, 0) == NULL);
	ASSERT_TEST(listFilter(list, NULL, 0) == NULL);
	ASSERT_TEST(listFilter(NULL, isLongerThan, 0) == NULL);

	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	int key = 2;
	List filtered = listFilter(list,isLongerThan, &key);

	ASSERT_TEST(listGetSize(filtered) == 3);
	ASSERT_TEST(strcmp(listGetCurrent(filtered),a[3])==0);

	ASSERT_TEST(strcmp(listGetFirst(filtered),a[3])==0);

	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	for ( int i = 3; i > 0; --i ){
		ASSERT_TEST( strcmp(listGetNext(list),a[i]) == 0);
	}

	listDestroy(list);
	listDestroy(filtered);
	return true;
}

static bool testListCopy() {
	ASSERT_TEST(listCopy(NULL) == NULL);

	List list = listCreate(copyString,freeString);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for ( int i = 0; i < 5; ++i ){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST( strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST( strcmp(listGetNext(list),a[3]) == 0);
	ASSERT_TEST( strcmp(listGetNext(list),a[2]) == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list),a[2]) == 0);
	ASSERT_TEST(listGetSize(list) == 5);

	List newList = listCopy(list);

	ASSERT_TEST(listGetSize(newList) == 5);
	ASSERT_TEST(strcmp(listGetCurrent(newList),a[2]) == 0);

	ASSERT_TEST(strcmp(listGetFirst(newList),a[4])==0);
	for ( int i = 3; i > 0; --i ){
		ASSERT_TEST( strcmp(listGetNext(newList),a[i]) == 0);
	}

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
	ASSERT_TEST(strcmp(listGetNext(list),a[3])==0);
	ASSERT_TEST(strcmp(listGetCurrent(list),a[3])==0);
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

	ASSERT_TEST( listGetNext(list) == NULL );
	ASSERT_TEST( listGetCurrent(list) == NULL );

	ASSERT_TEST( strcmp(listGetFirst(list),a[4] ) == 0);
	ASSERT_TEST( strcmp(listGetCurrent(list),a[4] ) == 0);
	ASSERT_TEST( strcmp(listGetCurrent(list),a[4] ) == 0);
	for (int i = 3; i >= 0; --i ){
		ASSERT_TEST( strcmp(listGetNext(list),a[i] ) == 0);
		ASSERT_TEST( strcmp(listGetCurrent(list),a[i] ) == 0);
	}
	ASSERT_TEST( strcmp(listGetCurrent(list),a[0] ) == 0);
	ASSERT_TEST( listGetNext(list) == NULL );
	ASSERT_TEST( strcmp(listGetCurrent(list),a[0] ) == 0);

	listDestroy(list);
	return true;
}

static bool testListGetCurrent() {
	ASSERT_TEST(listGetCurrent(NULL) == NULL);

	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetCurrent(list) == NULL);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i = 0 ; i < 5; ++i ){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST( listGetNext(list) == NULL);
	ASSERT_TEST(listGetCurrent(list) == NULL);

	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list),a[4]) == 0);
	for (int i = 3; i >= 0; --i ){
		ASSERT_TEST(strcmp(listGetNext(list),a[i]) == 0);
		ASSERT_TEST(strcmp(listGetCurrent(list),a[i]) == 0);
	}
	ASSERT_TEST(strcmp(listGetCurrent(list),a[0]) == 0);
	listDestroy(list);
	return true;
}

static bool testListInsertFirst() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	ASSERT_TEST( listInsertFirst(NULL,a[0]) == LIST_NULL_ARGUMENT );

	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetFirst(list) == NULL);

	for ( int i = 0; i < 5; ++i ){
		ASSERT_TEST( listInsertFirst(list,a[i]) == LIST_SUCCESS );
		ASSERT_TEST(strcmp(listGetFirst(list),a[i])==0);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4])==0);
	for ( int i = 3; i >= 0; --i ){
		ASSERT_TEST(strcmp(listGetNext(list),a[i])==0);
	}
	listDestroy(list);
	return true;
}

static bool testListInsertLast() {
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	ASSERT_TEST( listInsertLast(NULL,a[0]) == LIST_NULL_ARGUMENT );

	List list = listCreate(copyString,freeString);
	ASSERT_TEST(listGetFirst(list) == NULL);

	listInsertLast(list,a[0]);
	ASSERT_TEST(strcmp(listGetFirst(list),a[0])==0);

	for ( int i = 1; i < 5; ++i ){
		ASSERT_TEST( listInsertLast(list,a[i]) == LIST_SUCCESS );
	}
	ASSERT_TEST(strcmp(listGetFirst(list),a[0]) == 0);
	for ( int i = 1; i < 5; ++i ){
		ASSERT_TEST(strcmp(listGetNext(list),a[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListInsertBeforeCurrent() {
	//TODO what to do if list empty
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	ASSERT_TEST( listInsertBeforeCurrent(NULL,a[0]) == LIST_NULL_ARGUMENT );

	List list = listCreate(copyString,freeString);

	ASSERT_TEST( listInsertBeforeCurrent(list,a[0]) == LIST_INVALID_CURRENT );

	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
	ASSERT_TEST( listInsertBeforeCurrent(list,"ccc") == LIST_SUCCESS );

	char* b[6] = {"aaa","bbb","NI","ccc","hello mister fish","I"};
	ASSERT_TEST(strcmp(listGetFirst(list),b[5]) == 0);
	for (int i = 4; i >= 0; --i){
		ASSERT_TEST(strcmp(listGetNext(list),b[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListInsertAfterCurrent() {
	//TODO what to do if list empty
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	ASSERT_TEST( listInsertBeforeCurrent(NULL,a[0]) == LIST_NULL_ARGUMENT );

	List list = listCreate(copyString,freeString);

	ASSERT_TEST( listInsertAfterCurrent(list,a[0]) == LIST_INVALID_CURRENT );

	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
	ASSERT_TEST( listInsertAfterCurrent(list,"ccc") == LIST_SUCCESS );

	char* b[6] = {"aaa","bbb","ccc","NI","hello mister fish","I"};
	ASSERT_TEST(strcmp(listGetFirst(list),b[5]) == 0);

	for (int i = 4; i >= 0; --i){
		ASSERT_TEST(strcmp(listGetNext(list),b[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListRemoveCurrent() {
	ASSERT_TEST( listRemoveCurrent(NULL) == LIST_NULL_ARGUMENT );

	List list = listCreate(copyString,freeString);
	ASSERT_TEST( listRemoveCurrent(list) == LIST_INVALID_CURRENT );

	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
	ASSERT_TEST( listRemoveCurrent(list) == LIST_SUCCESS );
	ASSERT_TEST(strcmp(listGetCurrent(list),a[3]) == 0);

	char* b[4] = {"aaa","bbb","hello mister fish","I"};
	ASSERT_TEST(strcmp(listGetFirst(list),b[3]) == 0);

	for (int i = 2; i >= 0; --i){
		ASSERT_TEST(strcmp(listGetNext(list),b[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListSort() {
	List list = listCreate(copyString,freeString);

	ASSERT_TEST(listSort(NULL,NULL) == LIST_NULL_ARGUMENT);
	ASSERT_TEST(listSort(list,NULL) == LIST_NULL_ARGUMENT);
	ASSERT_TEST(listSort(NULL, compareStringLength) == LIST_NULL_ARGUMENT);

	char* a[5] = {"aaaaa","bbb","AI","hello mister fish","I"};
	for (int i = 0; i < 5; ++i ){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[3]) == 0);
	ASSERT_TEST(strcmp(listGetNext(list),a[2]) == 0);
	ASSERT_TEST(strcmp(listGetCurrent(list),a[2]) == 0);

	ASSERT_TEST(strcmp(listGetFirst(list),a[4]) == 0);
	for (int i = 3; i >= 0; --i ){
		ASSERT_TEST(strcmp(listGetNext(list),a[i]) == 0);
	}
	ASSERT_TEST(listSort(list,compareLexiStringLexicographical)==LIST_SUCCESS);
	//TODO - check iterator location
	//ASSERT_TEST(strcmp(listGetCurrent(list),a[2]) == 0);

	char* b[5] = {"AI","I","aaaaa","bbb","hello mister fish"};
	ASSERT_TEST(strcmp(listGetFirst(list),b[0]) == 0);
	for (int i = 1; i < 5; ++i ){
		ASSERT_TEST(strcmp(listGetNext(list),b[i]) == 0);
	}
	ASSERT_TEST(listSort(list,compareStringLength)==LIST_SUCCESS);

	char* c[5] = {"I","AI","bbb","aaaaa","hello mister fish"};
	ASSERT_TEST(strcmp(listGetFirst(list),c[0]) == 0);
	for (int i = 1; i < 5; ++i ){
		ASSERT_TEST(strcmp(listGetNext(list),c[i]) == 0);
	}
	listDestroy(list);
	return true;
}

static bool testListClear() {
	ASSERT_TEST(listClear(NULL) == LIST_NULL_ARGUMENT);

	List list = listCreate(copyString,freeString);
	char* a[5] = {"aaa","bbb","NI","hello mister fish","I"};
	for (int i=0;i <5; ++i){
		listInsertFirst(list,a[i]);
	}
	ASSERT_TEST(listGetSize(list) == 5);
	listClear(list);
	ASSERT_TEST(listGetSize(list) == 0);
	ASSERT_TEST(listGetFirst(list) == NULL);
	listDestroy(list);
	return true;
}

static bool testListDestroy() {

	listDestroy(NULL);

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
	RUN_TEST(testListGetCurrent);
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
