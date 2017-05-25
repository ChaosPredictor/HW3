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
	ListElementNode first;
	ListElementNode iterator;
	int size;
	CopyListElement copy;
	FreeListElement free;
};


static ListElementNode listElementNodeCreate(ListElement listElement);
static ListElementNode listInsert (List list, ListElement element);

List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
	if (copyElement == NULL || freeElement == NULL) return NULL;
	List list = malloc(sizeof(*list));
	if (list == NULL) {
		return NULL;
	}
	list->first = NULL;
	list->iterator = NULL;
	list->size = 0;
	list->copy = copyElement;
	list->free = freeElement;
	return list;
}

List listCopy(List list) {
	if ( list == NULL) return NULL;
	List newList = listCreate(list->copy, list->free);
	ListElementNode tempListElementNode = list->first;

	while( tempListElementNode != NULL) {
		ListResult result = listInsertLast(newList, tempListElementNode->data);
		if ( result != LIST_SUCCESS ) {
			listDestroy(newList);
			return NULL;
		}
		tempListElementNode = tempListElementNode->next;
	}
	return newList;
}

int listGetSize(List list) {
	if ( list == NULL) return -1;
	return list->size;
}

ListElement listGetFirst(List list) {
	//TODO move iterator to start
	if ( list == NULL ) return NULL;
	if ( list->first == NULL) return NULL;
	list->iterator = list->first;
	return list->first->data;
}

ListElement listGetNext(List list) {
	if ( list == NULL ) return NULL;
	if ( list->first == NULL) return NULL;
	if ( list->iterator == NULL) return NULL;
	if ( list->iterator->next == NULL) return NULL;
	list->iterator = list->iterator->next;
	return list->iterator->data;
}

ListElement listGetCurrent(List list) {
	if ( list == NULL ) return NULL;
	if ( list->first == NULL) return NULL;
	if ( list->iterator == NULL) return NULL;
	return list->iterator->data;
}

ListResult listInsertFirst(List list, ListElement listElement) {
	if ( list == NULL) return LIST_NULL_ARGUMENT;

	ListElementNode newNode = listInsert(list, listElement);
	if ( newNode == NULL) return LIST_OUT_OF_MEMORY;

	newNode->next = list->first;
	list->first = newNode;

	list->size++;
	return LIST_SUCCESS;
}

ListResult listInsertLast(List list, ListElement listElement) {
	//TODO remove duplication of listInsert;
	if ( list == NULL) return LIST_NULL_ARGUMENT;

	ListElementNode newNode = listInsert(list, listElement);
	if ( newNode == NULL) return LIST_OUT_OF_MEMORY;

	ListElementNode tempListElementNode = list->first;
	if ( tempListElementNode != NULL) {
		while ( tempListElementNode->next != NULL ) {
			tempListElementNode = tempListElementNode->next;
		}
		tempListElementNode->next = newNode;
	} else {
		list->first = newNode;
	}
	list->size++;

	return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element) {
	if ( list == NULL) return LIST_NULL_ARGUMENT;

	ListElementNode newNode = listInsert(list, element);
	if ( newNode == NULL) return LIST_OUT_OF_MEMORY;

	newNode->next = list->iterator;

	ListElementNode listElementNode = list->first;
	while ( listElementNode->next != list->iterator ) {
		//printf("\n%s\n",(char*)listElementNode->data);
		listElementNode = listElementNode->next;
	}
	listElementNode->next = newNode;
	//list->iterator->next = newNode;
	list->size++;
	return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element) {
	if ( list == NULL) return LIST_NULL_ARGUMENT;

	ListElementNode newNode = listInsert(list, element);
	if ( newNode == NULL) return LIST_OUT_OF_MEMORY;

	newNode->next = list->iterator->next;

	list->iterator->next = newNode;
	list->size++;
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
		list->size--;
	}
	return LIST_SUCCESS;
}

void listDestroy(List list) {
	if ( list == NULL ) return;
	listClear(list);
	list->first = NULL;
	list->size = 0;
	free(list);
	list = NULL;
}

static ListElementNode listElementNodeCreate(ListElement listElement) {
	ListElementNode listElementNode = malloc(sizeof(*listElementNode));
	if( listElementNode == NULL ) return NULL;

	listElementNode->data = listElement;
	listElementNode->next = NULL;
	return listElementNode;
}

void ListPrint(List list) {
	ListElementNode listElementNode = list->first;
	while (listElementNode != NULL) {
		printf("\n%s\n", (char*)listElementNode->data);
		listElementNode = listElementNode->next;
	}
}

static ListElementNode listInsert (List list, ListElement element) {
	ListElement newListElement = list->copy(element);
	if ( newListElement == NULL ) return NULL;

	ListElementNode newNode = listElementNodeCreate(newListElement);
	if ( newNode == NULL ) {
		free(newListElement);
		return NULL;
	}
	return newNode;
}


