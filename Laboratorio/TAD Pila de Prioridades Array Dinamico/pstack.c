#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack 
{
    struct s_node **array;
    priority_t max_priority;
    unsigned int size;
};

struct s_node 
{
    pstack_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e) 
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->next = NULL;
    
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) 
{
    free(node);
    node = NULL;
    return node;
}

static bool invrep(pstack s) 
{
   return s != NULL;
}

pstack pstack_empty(priority_t max_priority) 
{
    pstack s = malloc(sizeof(struct s_pstack));
    
    s->array = malloc((max_priority + 1) * sizeof(struct s_node));
    s->size = 0;
    s->max_priority = max_priority;
    for (priority_t i = 0; i <= max_priority; i++)
    {
        s->array[i] = NULL;
    }
    
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) 
{
    assert(invrep(s) && priority <= s->max_priority);
    struct s_node *new_node = create_node(e);

    if (s->array[priority] == NULL)
    {
        s->array[priority] = new_node;
    }
    else
    {
        new_node->next = s->array[priority];
        s->array[priority] = new_node;  
    }
    s->size = s->size + 1;
    assert(invrep(s) && !pstack_is_empty(s));
    
    return s;
}

bool pstack_is_empty(pstack s) 
{
    assert(invrep(s));
    return s->size == 0;
}

pstack_elem pstack_top(pstack s) 
{
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t i = s->max_priority;
    while (s->array[i] == NULL)
    {
        i = i - 1;
    }

    return s->array[i]->elem;
}

priority_t pstack_top_priority(pstack s) 
{
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t i = s->max_priority;
    while (s->array[i] == NULL)
    {
        i = i - 1;
    }

    return i;
}

size_t pstack_size(pstack s) 
{
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) 
{
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node *killme = NULL;
    priority_t i = s->max_priority;
    
    while (s->array[i] == NULL)
    {
        i = i - 1;

    }
    killme = s->array[i];
    s->array[i] = s->array[i]->next;
    destroy_node(killme);
    s->size = s->size - 1;
    assert(invrep(s));
    
    return s;
}

pstack pstack_destroy(pstack s)
{
    assert(invrep(s));

    for (size_t i = 0; i <= s->max_priority; i++) 
    {
        struct s_node *killme = s->array[i];
        while (killme != NULL) 
        {
            struct s_node *next = killme->next;
            destroy_node(killme);
            killme = next;
        }
        s->array[i] = NULL;
    }
    free(s->array);
    free(s);
    s = NULL;
    
    return s;
}
