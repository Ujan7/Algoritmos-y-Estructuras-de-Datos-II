#ifndef _LIST_H
#define _LIST_H
#include <stdbool.h>

typedef int list_elem;
typedef struct node *list;

list empty_list();
/*Creates an empty list*/

list addl(list l, list_elem e);
/*Adds the current element e to the passed list as a parametrer*/

bool is_empty_list(list l);
/*Returns true if the actual list is empty*/

list_elem head(list l);
/*Returns the first element of the current list*/
/*PRE: != is_empty_list*/

list tail(list l);
/*Returns the list without the first element*/
/*PRE: != is_empty_list*/

list addr(list l, list_elem e);
/*Adds the current element e at the end of the list*/

unsigned int length(list l);
/*Returns the size of the actual list*/

list concat(list l1, list l2);
/*Returns a new list that contains the elemens of l1, and at the end the elemets of l2*/

list_elem index(list l, unsigned int position);
/*Returns the element of a determined position*/
/*PRE: length(l) > position*/

list take(list l, unsigned int n);
/*Returns the list with only the first n elements*/

list drop(list l, unsigned int n);
/*Returns the list with the n last elements*/

list copy_list(list l);
/*Copys all the elemets of l1 to a new list*/

list destroy(list l);
/*Frees memory if its necessary*/


#endif