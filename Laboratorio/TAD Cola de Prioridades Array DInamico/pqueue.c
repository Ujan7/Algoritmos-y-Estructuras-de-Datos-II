#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue 
{
    size_t q_size;
    priority_t min_priority;
    struct s_node **array;
};

struct s_node 
{
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) 
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    
    new_node->elem = e;
    new_node->next = NULL;
    
    return new_node;
}

static struct s_node *destroy_node(struct s_node *node) 
{
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) 
{
    bool invrep_ = (q != NULL);
    size_t check_size = 0;
    struct s_node *index;

    if (invrep_)
    {
        for (unsigned int i = 0; i <= q->min_priority; i++)
        {
            index = q->array[i];
            while (index != NULL)
            {
                index = index->next;
                check_size = check_size + 1;
            }

            invrep_ = check_size == q->q_size;
        }
    }

    return invrep_;
}

pqueue pqueue_empty(priority_t min_priority) 
{
    pqueue q = malloc (sizeof(struct s_pqueue));
    
    q->q_size = 0;
    q->min_priority = min_priority;
    q->array = malloc((min_priority + 1) * sizeof(struct s_node));
     
    for (priority_t i = 0; i <= min_priority; i++)
    {
        q->array[i] = NULL;
    }
    
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) 
{
    assert(invrep(q));
    assert(priority <= q->min_priority);
    struct s_node *insert_elem;
    struct s_node *new_node = create_node(e);
  
    if (q->array[priority] == NULL)
    {
        q->array[priority] = new_node;
    }
    else 
    {
        insert_elem = q->array[priority];
        while (insert_elem->next != NULL)
        {
            insert_elem = insert_elem->next; 
        }

        insert_elem->next = new_node; 
    }

    q->q_size = q->q_size + 1;

    assert(invrep(q) && !pqueue_is_empty(q));
    return q;
}

bool pqueue_is_empty(pqueue q) 
{
    assert(invrep(q));
    return q->q_size == 0;
}

pqueue_elem pqueue_peek(pqueue q) 
{
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t i = 0;
    while (q->array[i] == NULL)
    {
       i = i + 1;
    }

    return q->array[i]->elem;
}

priority_t pqueue_peek_priority(pqueue q) 
{
    assert(invrep(q) && !pqueue_is_empty(q));
    priority_t i = 0;
    while (q->array[i] == NULL)
    {
        i = i + 1;
    }

    return i;
}

size_t pqueue_size(pqueue q) 
{
    assert(invrep(q));
    return q->q_size;
}

pqueue pqueue_dequeue(pqueue q) 
{
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *killme = NULL;
    priority_t i = 0;

    while (q->array[i] == NULL)
    {
        i = i + 1;
    }

    killme = q->array[i];
    q->array[i] = q->array[i]->next;
    destroy_node(killme);
    q->q_size = q->q_size - 1;
    
    assert(invrep(q));
    return q;
}

pqueue pqueue_copy(pqueue original)
{
    assert(invrep(original));
    
    pqueue copy = pqueue_empty(original->min_priority);
    priority_t i;
    
    for (i = 0; i <= original->min_priority; i++)
    {
        struct s_node *index = original->array[i];
        
        while (index != NULL)
        {
            copy = pqueue_enqueue(copy, index->elem, i);
            index = index->next;
        }
    }
    
    assert(invrep(copy));
    return copy;
}


pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));

    for (size_t i = 0; i <= q->min_priority; i++) 
    {
        struct s_node *killme = q->array[i];
        while (killme != NULL) 
        {
            struct s_node *next = killme->next;
            destroy_node(killme);
            killme = next;
        }
        q->array[i] = NULL;
    }

    free(q->array);
    free(q);
    q = NULL;
    return q;
}

