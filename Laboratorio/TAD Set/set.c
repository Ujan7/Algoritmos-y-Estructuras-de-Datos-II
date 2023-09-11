#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

struct s_node {
    set_elem elem;
    struct s_node *next;
};

typedef struct s_node * node_t;

struct s_set {
    unsigned int size;
    node_t first;
};

static bool invrep(set s) 
{
    bool inv = s != NULL;
    unsigned int size = 0;
    node_t check_index = s->first;
    
    while (check_index != NULL)
    {
        size = size + 1;
        inv = check_index->next == NULL || check_index->elem < check_index->next->elem;
        check_index = check_index->next;
    }

    return inv && (s->size == size);
}

static struct s_node *create_node(set_elem e) 
{
    node_t new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->next = NULL;

    return new_node;
}

static struct s_node *destroy_node(struct s_node *node)
{
   free(node);
   node = NULL;
   return node;
}

/* CONSTRUCTORS */

set set_empty(void) 
{
    set empty_set = malloc(sizeof(struct s_set));
    empty_set->first = NULL;
    empty_set->size = 0;
    
    assert(invrep(empty_set));
    return empty_set;  
}

set set_add(set s, set_elem e) 
{
    assert(invrep(s));
    if (set_member(e, s))
    {
        return s;
    }
    else 
    {
        node_t actual_index = s->first;
        node_t bef_actual_index = NULL;
        node_t new_node = create_node(e);
    
        while(actual_index != NULL && e > actual_index->elem)
        {
            bef_actual_index = actual_index;
            actual_index = actual_index->next;
        }
        if (bef_actual_index == NULL)
        {
            new_node->next = s->first;
            s->first = new_node;
        }
        else
        {
            new_node->next = actual_index;
            bef_actual_index->next = new_node;
        }
        s->size = s->size + 1;
        assert(invrep(s));
        
        return s;
    }
}

/* OPERATIONS   */
unsigned int set_cardinal(set s) 
{
    assert(invrep(s));
    return s->size;
}

bool set_is_empty(set s) 
{
    assert(invrep(s));
    return s->size == 0;
}

bool set_member(set_elem e, set s) 
{
    assert(invrep(s));
    assert(invrep(s));
    node_t node = s->first;
    while (node != NULL && node->elem < e) 
    {
        node = node->next;
    }
    return node != NULL && node->elem == e;
}


set set_elim(set s, set_elem e) 
{
    assert(invrep(s));
    if (!set_member(e, s))
    {
        return s;
    }
    
    node_t killme = s->first;
    node_t bef_killme = NULL;
    
    while (killme != NULL && e != killme->elem)
    {
        bef_killme = killme;
        killme = killme->next;
    }

    if (bef_killme == NULL)
    {
        s->first = s->first->next;
        
    }
    else
    {
        bef_killme->next = killme->next;
    }

    destroy_node(killme);
    s->size = s->size - 1;
    assert(invrep(s));
    return s;
}

set_elem set_get(set s) 
{
    assert(invrep(s) && !set_is_empty(s));
    return s->first->elem;
}

set_elem *set_to_array(set s) 
{
    assert(invrep(s));
    node_t actual_index = s->first;
    set_elem *array = malloc(s->size * (sizeof(set_elem)));
    
    for (unsigned int i = 0; i < s->size; i++)
    {
        array[i] = actual_index->elem;
        actual_index = actual_index->next;
    }

    return array;
}

set set_destroy(set s) 
{
    assert(invrep(s));
    node_t killme = NULL;
    while (s->first != NULL)
    {
        killme = s->first;
        s->first = s->first->next;
        destroy_node(killme);
    }
    s->first = NULL;
    s->size = 0;
    free(s);
    s = NULL;

    return s;
}

