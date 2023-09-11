#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack 
{
    size_t size;
    struct s_node *front;
};

struct s_node 
{
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) 
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);

    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
    
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) 
{
    assert(node != NULL);
    
    free(node);
    node = NULL;
    
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) 
{
    bool invrep_ = s != NULL;
    struct s_node *check_index = s->front;
    size_t actual_size = 0;

    while (check_index != NULL)
    {
        invrep_ = check_index->next == NULL || check_index->priority >= check_index->next->priority;
        actual_size = actual_size + 1;
        check_index = check_index->next;
    }
    
    return invrep_ && (actual_size == s->size);
}

pstack pstack_empty(void) 
{
    pstack s = malloc(sizeof(struct s_pstack));

    s->front = NULL;
    s->size = 0;
    
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) 
{
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *curr_index = s->front;
    struct s_node *bef_curr_index = NULL;

    while(curr_index != NULL && priority < curr_index->priority)
    {
        bef_curr_index = curr_index;
        curr_index = curr_index->next;
    }

    if (bef_curr_index == NULL)
    {
        new_node->next = curr_index;
        s->front = new_node;   
    }
    else
    {
        bef_curr_index->next = new_node;
        new_node->next = curr_index;
    }
    s->size = s->size + 1;
    
    assert(invrep(s));
    return s;
}

bool pstack_is_empty(pstack s) 
{
    return (s->size == 0);
}

pstack_elem pstack_top(pstack s) 
{
    return s->front->elem;
}

priority_t pstack_top_priority(pstack s) 
{
    return s->front->priority;
}

unsigned int pstack_size(pstack s) 
{
    assert(invrep(s));
    
    return s->size;
}

pstack pstack_pop(pstack s) 
{
    assert(invrep(s));
    struct s_node *killme = s->front;
    
    s->front = s->front->next;
    killme = destroy_node(killme);
    s->size = s->size - 1;
   
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) 
{
    assert(invrep(s));
    struct s_node *killme;
    while (s->front != NULL)
    {
        killme = s->front;
        s->front = killme->next;
        killme = destroy_node(killme);
    }
    
    free(s);
    s = NULL;

    assert(s == NULL);
    return s;
}
