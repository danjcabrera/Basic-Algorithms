//
// list-example.c
//


#include <stdio.h>
#include <stdlib.h>
#include "myllist.h"

// print_list                                                                   
static void print_list(const List *list) {                                      
        ListElmt        *element;                                               
        int             *data, i;                                               
                                                                                 
        fprintf(stdout, "List size is %d\n", list_size(list));                  
        element = list_head(list);                                              
                                                                                
        while(1) {                                                              
                data = (int *)list_data(element);                               
                                                                                
                fprintf(stdout, "list[%03d]=%03d\n", i, *data);                 
                                                                                
                i++;                                                            
                                                                                
                if (list_is_tail(element))                                      
                        break;                                                  
                else                                                            
                        element = list_next(element);                           
        }                                                                       
                                                                                
        return;                                                                 
} 





int main(int argc, char **argv) {
	List		list;
	ListElmt	*element;
	int 		*data, i;

	list_init(&list, free);

	// ascertain head pointer
	element = list_head(&list);

	// populate a list of 10 items	
	for (i = 10; i > 0; i--) {
		if ((data = (int *)malloc(sizeof(int))) == NULL)
			return 1;
		
		*data = i;
	
		if (list_ins_next(&list, NULL, data) != 0)
			return 1;
	}

	print_list(&list);

	// ascertain head pointer
	element = list_head(&list);

	// delete element	
	// walk the stack to find the preceding element of the one to delete
	for(i = 0; i < 7; i++)
		element = list_next(element);	

	data = (int *)list_data(element);
	fprintf(stdout, "Removing an element after the one containing %03d\n", *data);

	if (list_rem_next(&list, element, (void **)&data) != 0)
		return 1;

	print_list(&list);


	// insert element at the tail
	fprintf(stdout, "Inserting 011 at the tail of the list\n");
	*data = 11;
	if (list_ins_next(&list, list_tail(&list), data) != 0)
		return 1;

	print_list(&list);


	// remove the next element after head
	fprintf(stdout, "Removing an element after the first element\n");

	element = list_head(&list);
	if (list_rem_next(&list, element, (void **)&data) != 0)
		return 1;

	print_list(&list);
		
	// delete the eighth element in the list 
        fprintf(stdout, "delete the eighth element of the list\n");

	for(i = 1; i < 7; i++)                                                  
                 element = list_next(element);                                   
                                                                                 
        data = (int *)list_data(element);                                       
                                                                                
        if (list_rem_next(&list, element, (void **)&data) != 0)                 
                return 1;                                                       
                                                                                 
        print_list(&list);           
	
	// insert a new head element (012)
	fprintf(stdout, "Inserting 012 at the head of the list\n");

	*data = 12;
	if (list_ins_next(&list, NULL, data) != 0)
		return 1;

	print_list(&list);

	// iterate through the list and remove the fourth element
	fprintf(stdout, "Iterating and removing the fourth element\n");
	element = list_head(&list);
	element = list_next(element);
	element = list_next(element);

	if (list_rem_next(&list, element, (void **)&data) != 0)
		return 1;

	print_list(&list);

	// insert an element after head
	fprintf(stdout, "Insert 013 after the first element\n");

	*data = 13;
	if (list_ins_next(&list, list_head(&list), data) != 0)
		return 1;

	print_list(&list);

	// destroy the list
	fprintf(stdout, "Destroying the list\n");
	list_destroy(&list);


	return 0;
}

