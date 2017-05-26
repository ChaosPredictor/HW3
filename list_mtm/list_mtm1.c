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
static ListResult exchangeNode(List list, ListElementNode listElementNode1, \
		ListElementNode listElementNode2);

List listCreate(CopyListElement copyElement, FreeListElement freeElement) {
	if (copyElement == NULL || freeElement == NULL) return NULL;
	List list = malloc(sizeof(*list));
	if (list == NULL) return NULL;
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
	if ( newList == NULL ) return NULL;

	ListElementNode tempListElementNode = list->first;
	ListElementNode currentNode;

	while( tempListElementNode != NULL) {

		ListElementNode newNode = listInsert(newList,tempListElementNode->data);

		if( newNode == NULL) {
			listDestroy(newList);
			return NULL;
		}
		if ( newList->first == NULL ) {
			newList->first = newNode;
		} else {
			currentNode->next = newNode;
		}

		if( list->iterator == tempListElementNode ) {
			newList->iterator = newNode;
		}

		currentNode = newNode;
		newList->size++;

		tempListElementNode = tempListElementNode->next;
	}

	return newList;
}

int listGetSize(List list) {
	if ( list == NULL ) return -1;
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
	if ( list->iterator == NULL ) return NULL;
	if ( list->iterator->next == NULL ) return NULL;
	list->iterator = list->iterator->next;
	return list->iterator->data;
}

ListElement listGetCurrent(List list) {
	if ( list == NULL ) return NULL;
	if ( list->first == NULL ) return NULL;
	if ( list->iterator == NULL ) return NULL;
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
	if ( list->iterator == NULL) return LIST_INVALID_CURRENT;

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
	if ( list->iterator == NULL ) return LIST_INVALID_CURRENT;

	ListElementNode newNode = listInsert(list, element);
	if ( newNode == NULL) return LIST_OUT_OF_MEMORY;

	newNode->next = list->iterator->next;

	list->iterator->next = newNode;
	list->size++;
	return LIST_SUCCESS;
}

ListResult listRemoveCurrent(List list) {
	if ( list == NULL) return LIST_NULL_ARGUMENT;

	if ( list->iterator == NULL) return LIST_INVALID_CURRENT;

	ListElementNode listElementNode = list->first;
	while ( listElementNode->next != list->iterator ) {
		listElementNode = listElementNode->next;
	}

	listElementNode->next = list->iterator->next;
	list->free(list->iterator->data);
	free(list->iterator);
	list->iterator = NULL;
	return LIST_SUCCESS;
}

ListResult listSort(List list, CompareListElements compareElement) {
	if ( list == NULL || compareElement == NULL) return LIST_NULL_ARGUMENT;

	List listTemp = listCopy(list);
	if ( listTemp == NULL) return LIST_OUT_OF_MEMORY;

	ListElementNode listElementNode1 = list->first;
	ListElementNode listElementNode2 = listElementNode1->next;
	ListResult result = LIST_SUCCESS;
	while (listElementNode1->next != NULL) {
		while( listElementNode2 != NULL) {
			if(compareElement(listElementNode1->data,listElementNode2->data)>0){
				result = exchangeNode(list, listElementNode1, listElementNode2);
				if( result != LIST_SUCCESS ) {
					listDestroy(list);
					list = listCopy(listTemp);
					listDestroy(listTemp);
					return LIST_OUT_OF_MEMORY;
				}
			}
			listElementNode2 = listElementNode2->next;
		}
		listElementNode1 = listElementNode1->next;
		listElementNode2 = listElementNode1->next;
	}
	ListElementNode listElementNode = listTemp->first;
	if ( listTemp->iterator == NULL) {
		list->iterator = NULL;
	} else {
		int counter = 0;
		while(listElementNode != NULL && listTemp->iterator != listElementNode){
			listElementNode = listElementNode->next;
			counter++;
		}
		listElementNode = list->first;
		for(int i = 0; i < counter; i++) {
			listElementNode = listElementNode->next;
		}
		list->iterator = listElementNode;
	}
	listDestroy(listTemp);
	return LIST_SUCCESS;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key) {
	if ( list == NULL || filterElement == NULL) return NULL;

	ListElementNode listElementNode = list->first;
	if ( listElementNode == NULL ) return NULL;

	List newList = listCreate(list->copy, list->free);

	ListElementNode lastNode = NULL;
	while (listElementNode != NULL) {
		ListElement listElement = listElementNode->data;
		if ( filterElement(listElement, key) ) {
			ListElementNode currentNode = listInsert(newList, listElement);
			if ( currentNode == NULL) {
				listDestroy(newList);
				return NULL;
			}
			if ( newList->first == NULL ) {
				newList->first = currentNode;
			} else {
				lastNode->next = currentNode;
			}
			lastNode = currentNode;
			newList->size++;
		}
		listElementNode = listElementNode->next;
	}
	newList->iterator = newList->first;
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

static ListElementNode listInsert(List list, ListElement element) {
	ListElement newListElement = list->copy(element);
	if ( newListElement == NULL ) return NULL;

	ListElementNode newNode = listElementNodeCreate(newListElement);
	if ( newNode == NULL ) {
		free(newListElement);
		return NULL;
	}
	return newNode;
}

static ListResult exchangeNode(List list, ListElementNode listElementNode1, \
		ListElementNode listElementNode2) {
	//TODO to ask if it's a good way
	ListElement listElementTemp = list->copy(listElementNode1->data);
	if( listElementTemp == NULL ) return LIST_OUT_OF_MEMORY;
	list->free(listElementNode1->data);
	listElementNode1->data = list->copy(listElementNode2->data);
	if( listElementNode1 == NULL ) {
		list->free(listElementTemp);
		return LIST_OUT_OF_MEMORY;
	}
	list->free(listElementNode2->data);
	listElementNode2->data = list->copy(listElementTemp);
	list->free(listElementTemp);
	if( listElementNode2 == NULL ) {
		return LIST_OUT_OF_MEMORY;
	}
	return LIST_SUCCESS;
}


