#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue
{
    struct s_node *front;
    unsigned int size;    
};

struct s_node
{
    pqueue_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade,unsigned int approved_courses)
{
    float priority = 0.5 * (average_grade/MAX_GRADE) + 0.5 * (approved_courses/TOTAL_COURSES);
    return priority;
}

static struct s_node *create_node (pqueue_elem e,float average_grade,unsigned int approved_courses)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    float priority = calculate_priority(average_grade, approved_courses);
    
    assert(new_node != NULL);
    new_node->priority = priority;
    new_node->average_grade = average_grade;
    new_node->elem = e;
    new_node->approved_courses = approved_courses;
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
    bool subinv = q != NULL;
    struct s_node *check_index = q->front;
    unsigned int size = 0;

    while (subinv && check_index != NULL)
    {
        size = size + 1;
        subinv = check_index->next == NULL || check_index->priority >= check_index->next->priority;
        check_index = check_index->next;
    }

    return subinv && (size == q->size);
}

pqueue pqueue_empty(void)
{
    pqueue q = malloc(sizeof(struct s_pqueue));
    
    q->front = NULL;
    q->size = 0;
    
    assert(invrep(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, float average_grade, unsigned int approved_courses)
{
    assert(invrep(q));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    struct s_node *curr = q->front;
    struct s_node *bef_curr = NULL;

    while (curr != NULL && new_node->priority <= curr->priority)
    {
        bef_curr = curr;
        curr = curr->next;
    }
    if (bef_curr == NULL)
    {
        new_node->next = q->front;
        q->front = new_node;
    }
    else
    {
        new_node->next = curr;
        bef_curr->next = new_node;
    }
    q->size = q->size + 1;
    assert(invrep(q));
    
    return q;
}

bool pqueue_is_empty(pqueue q)
{
    assert(invrep(q));
    return q->size == 0;
}


pqueue_elem pqueue_peek(pqueue q)
{
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->front->elem;
}

float pqueue_peek_average_grade(pqueue q)
{   
    assert(invrep(q));
    return q->front->average_grade;
}

unsigned int pqueue_peek_approved_courses(pqueue q)
{
    assert(invrep(q));
    return q->front->approved_courses;
}

float pqueue_peek_priority(pqueue q)
{
    assert(invrep(q));
    return q->front->priority;
}

unsigned int pqueue_size(pqueue q)
{
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_copy(pqueue q)
{
    assert(invrep(q));
    pqueue copied_q = pqueue_empty();
    struct s_node *actual_index = q->front;
    struct s_node *act_index_cpy = NULL; // Variable para el nodo actual de la pila copiada

    while (actual_index != NULL)
    {
        // Creamos un nuevo nodo con los mismos valores
        struct s_node *new_node = create_node(actual_index->elem, actual_index->average_grade, actual_index->approved_courses);

        if (copied_q->front == NULL)
        {
            // Si la pila copiada está vacía, el nuevo nodo será el frente
            copied_q->front = new_node;
            act_index_cpy = copied_q->front;
        }
        else
        {
            // Enlazamos el nuevo nodo al nodo actual de la pila copiada
            act_index_cpy->next = new_node;
            act_index_cpy = act_index_cpy->next;
        }

        actual_index = actual_index->next;
    }

    copied_q->size = q->size;

    assert(invrep(copied_q));
    return copied_q;
}

pqueue pqueue_dequeue(pqueue q)
{
    assert(invrep(q));
    struct s_node *killme = q->front;
   
    q->front = q->front->next;
    killme = destroy_node(killme);
    q->size = q->size - 1;

    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q)
{
    assert(invrep(q));
    struct s_node *killme = NULL;
    while (q->front != NULL)
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
