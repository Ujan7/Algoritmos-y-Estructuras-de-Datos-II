#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "list.h"

struct _node_t {
  unsigned int key;
  list_value value;
  struct _node_t *next;
};

typedef struct _node_t * node_t;

struct _list_t {
  unsigned int size;
  node_t elems;
};

static bool invrep(list_t list) 
{
  bool inv = list != NULL;
  node_t curr = list->elems;
  
  while(inv && curr != NULL)
  {
    inv = curr->next == NULL || curr->key < curr->next->key;
    curr = curr->next;
  }

  return inv;
}

static struct _node_t * create_node(unsigned int key, list_value value) 
{
  node_t new_node = malloc(sizeof(struct _node_t));
  new_node->key = key;
  new_node->value = value;
  new_node->next = NULL;
  assert(new_node != NULL);
  return new_node;
}

static struct _node_t * destroy_node(struct _node_t *node) 
{
  free(node);
  return NULL;
}

list_t list_empty(void) 
{
  list_t list = NULL;
  list = malloc(sizeof(struct _list_t));
  
  list->elems = NULL;
  list->size = 0;
  
  assert(invrep(list));
  return list;
}

list_t list_add(list_t list, unsigned int key, list_value value) 
{
  assert(invrep(list));
  node_t node = create_node(key, value);
  assert(node != NULL);

  if (list->size == 0) 
  {
    list->elems = node;
  } 
  else if (list_exists(list, key)) 
  {
    node_t replace = list->elems;
    while (replace->key != key) 
    {
      replace = replace->next;
    }
    replace->value = value;  //Actualizamos el valor
    destroy_node(node);      //destruimos el nodo creado
  } 
  else 
  {
    node_t replace = list->elems;
    node_t prev = NULL;
    while (replace != NULL && replace->key < key) 
    {
      prev = replace;
      replace = replace->next;
    }
    if (prev == NULL) 
    {
      // Insertar al principio de la lista
      node->next = list->elems;
      list->elems = node;
    } 
    else 
    {
      // Insertar en otro lugar de la lista
      prev->next = node;
      node->next = replace;
    }
  }
  list->size++;
  assert(invrep(list) && value == list_search(list, key));
  
  return list;
}

unsigned int list_length(list_t list) 
{
  assert(invrep(list));
  return list->size;
}

bool list_is_empty(list_t list) 
{
  assert(invrep(list));
  return list->size == 0;
}

bool list_exists(list_t list, unsigned int key) 
{
  assert(invrep(list));
  node_t cursor = list->elems;
  
  while (cursor != NULL && cursor->key < key) 
  {
    cursor = cursor->next;
  }
  
  return cursor != NULL && cursor->key == key;
}

char list_search(list_t list, unsigned int key) 
{
  assert(invrep(list));
  assert(list_exists(list, key));
  node_t search = list->elems;
  
  while (search->key != key)
  {
    search = search->next;
  }

  return search->value;
}

list_t list_remove(list_t list, unsigned int key) 
{
  assert(invrep(list));
  if (!list_exists(list, key)) 
  {
    return list;
  }

  node_t remove = list->elems;
  node_t bef = NULL;

  while (remove != NULL && remove->key != key) 
  {
    bef = remove;
    remove = remove->next;
  }

  if (bef == NULL) 
  {
    list->elems = remove->next;
  } 
  else 
  {
    bef->next = remove->next;
  }

  destroy_node(remove);
  list->size--;

  assert(invrep(list) && !list_exists(list, key));
  return list;
} 

list_t list_remove_all(list_t list) 
{
  node_t killme = NULL;
 
  while(list->elems != NULL)
  {
    killme = list->elems;
    list->elems = list->elems->next;
    killme = destroy_node(killme);
  }
  list->elems = NULL;
  list->size = 0;

  return list;
} 

list_value* list_to_array(list_t list) 
{
  assert(invrep(list));
  list_value *array = calloc(list->size, sizeof(list_value));
  node_t dump = list->elems;
  
  for (unsigned int i = 0; (dump != NULL) && (i<=list->size); i++)
  {
    array[i] = dump->value;
    dump = dump->next;
  }
  assert(invrep(list) && !list_is_empty(list));
  
  return array;
}

list_t list_destroy(list_t list) 
{
  list_remove_all(list);
  free(list);
  
  return NULL;
}