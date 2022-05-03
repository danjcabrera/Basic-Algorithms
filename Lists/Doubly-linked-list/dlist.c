// 
// dlist.c
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"


//------------------  dlist_init
void dlist_init(DList *list, void (*destroy)(void *data)) {
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}


//-----------------   dlist_ins_next
int dlist_ins_next(DList *list, DListElmt *element, const void *data) {
	
	DListElmt	*new_element;

	if (element == NULL && dlist_size(list) != 0)
		return -1;	

	// allocate storage
	if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	// insert new element
	new_element->data = (void *)data;

	if (dlist_size(list) == 0) {  // when list empty
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	} else {  // when list is not empty
		new_element->next = element->next;
		new_element->prev = element;

		if (element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;

		element->next = new_element;
	}
	// modify list size
	list->size++;

	return 0;
}


//----------------    dlist_ins_prev
int dlist_ins_prev(DList *list, DListElmt *element, const void *data) {
	
	DListElmt	*new_element;

	if (element == NULL && dlist_size(list) != 0)
		return -1;

	// allocate storage
	if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	// insert new element
	new_element->data = (void *)data;

	if (dlist_size(list) == 0) {  // when list empty
		list->head = new_element;
		list->head->prev = NULL;
		list->head->next = NULL;
		list->tail = new_element;
	} else {  // when list is not empty
		new_element->next = element;
		new_element->prev = element->prev;

		if (element->prev == NULL)
			list->head = new_element;
		else
			element->prev->next = new_element;

		element->prev = new_element;
	}
	// modify list size
	list->size++;
	
	return 0;
}


//----------------    dlist_remove
int dlist_remove(DList *list, DListElmt *element, void **data) {

	if (element == NULL || dlist_size(list) == 0)
		return -1;

	// remove element from list
	*data = element->data;

	if (element == list->head) { // if head
		list->head = element->next;

		if (list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;
	} else { // if other than head
		element->prev->next = element->next;

		if (element->next == NULL)
			list->tail = element->prev;
		else
			element->next->prev = element->prev;
	}

	free(element);

	list->size--;

	return 0;
}


//---------------     dlist_destroy
void dlist_destroy(DList *list) {

	void	*data;

	// remove each element
	while (dlist_size(list) > 0) {
		if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 
				&& list->destroy != NULL) {
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(DList));

	return;
}


//--------------      print_list
void print_list(const DList *list) {
	
	DListElmt	*element;
	int		*data, i;

	fprintf(stdout, "List size is %d\n", dlist_size(list));

	i = 0;
	element = dlist_head(list);

	while (1) {
		data = (int *)dlist_data(element);
		fprintf(stdout, "list[%03d]=%03d\n", i, *data);

		i++;

		if (dlist_is_tail(element))
			break;
		else
			element = dlist_next(element);
	}
	return;
}


//-------------       main
int main(int argc, char **argv) {
	
	DList		list;
	DListElmt	*element;
	int		*data, i;

	dlist_init(&list, free);

	element = dlist_head(&list);

	for (i = 10; i > 0; i--) {
		if ((data = (int *)malloc(sizeof(int))) == NULL)
			return 1;

		*data = i;

		if (dlist_ins_prev(&list, dlist_head(&list), data) != 0)
			return 1;
	}

	print_list(&list);

	element = dlist_head(&list);

	for (i = 0; i < 8; i++)
		element = dlist_next(element);

	data = (int *)dlist_data(element);
	fprintf(stdout, "Removing an element after the one container %03d\n", *data);

	if (dlist_remove(&list, element, (void **)&data) != 0)
		return 1;

	print_list(&list);

	return 0;
}

		



