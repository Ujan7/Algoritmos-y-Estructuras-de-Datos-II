#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue 
{
    struct s_node *front;
    unsigned int q_size;
};

struct s_node 
{
    pqueue_elem elem;
    unsigned int priority;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) 
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    
    new_node->elem = e;
    new_node->priority = priority;
    new_node->next = NULL;
  
    assert(new_node != NULL);
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


static bool invrep(pqueue q) 
{
    if (q == NULL)
    {
        return false;
    }

    return true; 
}

pqueue pqueue_empty(void) 
{
    pqueue empty_pqueue = malloc(sizeof(struct s_pqueue));

    empty_pqueue->front = NULL;
    empty_pqueue->q_size = 0;

    return empty_pqueue;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) 
{
    assert(invrep(q));
    struct s_node *enqueue_node = create_node(e, priority);
    if (pqueue_is_empty(q))
    {
        q->front = enqueue_node;
    }
    else
    {
        struct s_node *curr = q->front;
        struct s_node *bef_curr = NULL;

        while (curr != NULL && priority >= curr->priority)
        {
            bef_curr = curr;
            curr = curr->next;
        }

        if (bef_curr == NULL)
        {
            enqueue_node->next = curr;
            q->front = enqueue_node; 
        }
        else
        {
            enqueue_node->next = curr;
            bef_curr->next = enqueue_node;
        }
    }
    
    q->q_size = q->q_size + 1;

    assert(invrep(q));
    return q;
}

bool pqueue_is_empty(pqueue q) 
{
    return q->q_size == 0;
}

pqueue_elem pqueue_peek(pqueue q) 
{
    return q->front->elem;  
}

unsigned int pqueue_peek_priority(pqueue q) 
{
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q) 
{
    assert(invrep(q));
    
    return q->q_size; 
}

pqueue pqueue_dequeue(pqueue q) 
{
    struct s_node *killme = q->front;
    
    q->front = q->front->next;
    killme = destroy_node(killme);
    q->q_size = q->q_size - 1;
    
    return q;
}

pqueue pqueue_destroy(pqueue q) 
{
    assert(invrep(q));
    struct s_node *killme = q->front;

    while(killme != NULL)
    {
        killme = q->front;
        q->front = q->front->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    
    assert(q == NULL);
    return q;
}