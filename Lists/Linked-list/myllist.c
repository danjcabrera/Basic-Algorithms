//
// list.c
//

#include <stdlib.h>
#include <string.h>
#include "myllist.h"


//  list_init

void list_init(List *list, void (*destroy)(void *data)) {
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return ;
}


// list_ins_next

int list_ins_next(List *list, ListElmt *element, const void *data) {
	
	ListElmt	*new_element;

	// insertion	
	if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
		return -1;
	new_element->data = (void *)data;

	// insertion at the head of the list
	if (element == NULL) {
		if (list_size(list) == 0)
			list->tail = new_element;

		new_element->next = list->head;
		list->head = new_element;
	} else {  // insertion into the list 
		if (element->next == NULL)
			list->tail = new_element;
		new_element->next = element->next;
		element->next = new_element;
	}

	// modify the size of the list
	list->size++;

	return 0;
}


// list_rem_next

int list_rem_next(List *list, ListElmt *element, void **data) {
	ListElmt 	*old_element;

	// do not act on empty list
	if (list_size(list) == 0)
		return -1;
	
	// remove the head of the list
	if (element == NULL)  {
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1)
			list->tail = NULL;
	} else { //remove element from the list
		if (element->next == NULL)
			return -1;
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if (element->next == NULL)
			list->tail = element;
	}

	// free storage
	free(old_element);

	// modify the size
	list->size--;

	return 0;
}


// destroy_list
void list_destroy(List *list) {
	void	*data;

	while (list_size(list) > 0) {
		if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) {
				list->destroy(data);
		}
	}

	memset(list, 0, sizeof(List));

	return;
}



