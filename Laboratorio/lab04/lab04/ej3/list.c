#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

struct node
{
  list_elem elem;
  struct node *next;
};

list empty_list()
{
  return NULL;
}

list addl(list l, list_elem e)
{
  struct node *aux = malloc(sizeof(struct node));
  aux->elem = e;
  aux->next = l;
  l = aux;
  return l;
}

bool is_empty_list(list l)
{
  return l == NULL;
}

list_elem head(list l)
{
  assert(!is_empty_list(l));
  return l->elem;
}

list tail(list l)
{
  assert(!is_empty_list(l));
  list aux = l;
  l = l->next;
  free(aux);
  return l;
}

list addr(list l, list_elem e)
{
  list new_node = malloc(sizeof(struct node));
  list aux = NULL;
  new_node->elem = e;
  new_node->next = NULL;

  if (is_empty_list(l))
  {
    l = new_node;
  }
  else
  {
    aux = l;
    while (aux->next != NULL)
    {
      aux = aux->next;

    }
    aux->next = new_node;
  }

  return l;
}

unsigned int length(list l)
{
  unsigned int size_list = 0;
  
  list aux = l;
  while(aux != NULL)
  {
    aux = aux->next;
    size_list = size_list + 1;
  }

  return size_list;
}

void auxforConcat(list x, list y) 
{
  list aux = x;
  
  while(aux != NULL) 
  {
    addr(y, aux->elem);
  }
}

list concat(list list0,list list1) 
{
    list concat_list = empty_list();
    
    auxforConcat(list0, concat_list);
    auxforConcat(list1, concat_list);
    
    return concat_list;
  
}

list_elem index(list l, unsigned int position)
{
  assert(length(l) > position);
  list aux = l;
  for (unsigned int i = 0; i < position; i++)
  {
    aux = aux->next;
  }

  return aux->elem;
}

list take(list l, unsigned int n)
{
  if (l == NULL) {
    return NULL;
  }

  list elements_to_take = l; 
  list actual_elem = NULL;
  list elements_to_drop = NULL;

  for (unsigned int i = 0; i < n && elements_to_take != NULL; i++)
  {
    actual_elem = elements_to_take;
    elements_to_take = elements_to_take->next;
  } 
  
  if (actual_elem != NULL) {
    actual_elem->next = NULL;
  }
  
  while(elements_to_take != NULL)
  {
    elements_to_drop = elements_to_take;
    elements_to_take = elements_to_take->next;
    free(elements_to_drop);
  }

  return l;
}

list drop(list l, unsigned int n)
{
  list aux = l;
  list drop_e;
  unsigned int where_to_stop = 0;

  while(aux != NULL && where_to_stop < n) 
  {
    drop_e = aux;
    aux = aux->next;
    free(drop_e);
    where_to_stop = where_to_stop + 1;
  }
  l = aux;
  
  return l;
}

list copy_list(list l)
{
  list copied_list = empty_list();
  
  auxforConcat(l,copied_list);

  return copied_list;
}

list destroy(list l) 
{
  list aux = l;
  while (aux != NULL) {
    l = l->next;
    free(aux);
    aux = l;
  }
  return NULL;
}