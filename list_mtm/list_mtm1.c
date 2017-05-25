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

typedef struct listElementNode {
	void* data;
	struct listElementNode* next;
} *ListElementNode;


struct list_t {
	//TODO
	struct listElementNode* first;
	int size;
	//TODO maxSize?
	int iterator;
	CopyListElement copy;
	FreeListElement free;
};


static ListElementNode listElementNodeCreat(ListElement listElement);


List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
	//TODO
	if (copyElement == NULL || freeElement == NULL) return NULL;
	List list = malloc(sizeof(*list));
	if (list == NULL) {
		return NULL;
	}
	list->first = NULL;
	list->iterator = 0;
	list->size = 0;
	list->copy = copyElement;
	list->free = freeElement;
	return list;
}

List listCopy(List list) {
	//TODO
	return list;
}

int listGetSize(List list) {
	if ( list == NULL) {
		return -1;
	}
	return list->size;
}

ListElement listGetFirst(List list) {
	if ( list == NULL ) return NULL;
	if ( list->first == NULL) return NULL;
	return list->first->data;
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

ListResult listInsertFirst(List list, ListElement listElement) {
	if ( list == NULL) return LIST_NULL_ARGUMENT;

	//ListElementNode listElementNode = malloc(sizeof(*listElementNode));
	//if ( listElementNode == NULL ) return LIST_OUT_OF_MEMORY;
	ListElement newListElement = list->copy(listElement);
	if ( newListElement == NULL ) return LIST_OUT_OF_MEMORY;

	ListElementNode newNode = listElementNodeCreat(newListElement);
	if ( newNode == NULL ) {
		free(newListElement);
		return LIST_OUT_OF_MEMORY;
	}

	newNode->next = list->first;
	list->first = newNode;
	list->size++;
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
	if( list == NULL ) return LIST_NULL_ARGUMENT;
	while(list->first) {
		ListElementNode tempListElementNode = list->first;
		list->first = tempListElementNode->next;
		list->free(tempListElementNode->data);
		free(tempListElementNode);
	}
	return LIST_SUCCESS;
}

void listDestroy(List list) {
	//TODO
	listClear(list);
	free(list);
}

static ListElementNode listElementNodeCreat(ListElement listElement) {
	ListElementNode listElementNode = malloc(sizeof(*listElementNode));
	if( listElementNode == NULL ) return NULL;

	listElementNode->data = listElement;
	listElementNode->next = NULL;
	return listElementNode;
}
