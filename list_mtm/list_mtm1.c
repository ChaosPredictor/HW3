/*
 ============================================================================
 Name        : HW3.c
 Author      : kuzi
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "list_mtm1.h"
#include <stdio.h>
#include <stdlib.h>



List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
	//TODO
	if (copyElement == NULL || freeElement == NULL) return NULL;
	List list = malloc(sizeof(List*));
	return list;
}

List listCopy(List list) {
	//TODO
	return list;
}

int listGetSize(List list) {
	//TODO
	return 1;
}

ListElement listGetFirst(List list) {
	//TODO
	ListElement element = malloc(sizeof(ListElement));
	return element;
}

ListElement listGetNext(List list) {
	//TODO
	ListElement element = malloc(sizeof(ListElement));
	return element;
}

ListElement listGetCurrent(List list) {
	//TODO
	ListElement element = malloc(sizeof(ListElement));
	return element;
}

ListResult listInsertFirst(List list, ListElement element) {
	//TODO
	return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element) {
	//TODO
	return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element) {
	//TODO
	return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list) {
	//TODO
	return LIST_SUCCESS;
}

ListResult listSort(List list, CompareListElements compareElement) {
	//TODO
	return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key) {
	//TODO
	List newList = malloc(sizeof(List*));
	return newList;
}

ListResult listClear(List list) {
	//TODO
	return LIST_SUCCESS;
}

void listDestroy(List list) {
	//TODO
	free(list);
}
