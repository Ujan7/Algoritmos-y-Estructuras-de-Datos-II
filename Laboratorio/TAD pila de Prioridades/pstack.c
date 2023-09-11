#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack 
{
    unsigned int s_size;
    struct s_node *front;

};

struct s_node 
{
    pstack_elem elem;
    float average_grade;
    unsigned int approved_courses;
    float priority;
    struct s_node *next;
};


static float calculate_priority(float average_grade, unsigned int approved_courses)
{
    float priority = 0.3 * (average_grade/MAX_GRADE) + 0.7 * (approved_courses/TOTAL_COURSES);

    return priority;
}

static struct s_node *create_node(pstack_elem e,float average_grade,unsigned int approved_courses)
{
    struct s_node *new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    
    float priority = calculate_priority(average_grade, approved_courses);
    new_node->elem = e;
    new_node->priority = priority;
    new_node->average_grade = average_grade;
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

static bool invrep(pstack s)
{
    bool subinv = s != NULL;
    struct s_node *check_index = s->front;
    unsigned int size = 0;

    while (subinv && check_index != NULL)
    {
        size = size + 1;
        subinv = check_index->next == NULL || check_index->priority >= check_index->next->priority;
        check_index = check_index->next;
    }

    return subinv && (size == s->s_size);
}

pstack pstack_empty(void)
{
    pstack s = malloc(sizeof(struct s_pstack ));

    s->front = NULL;
    s->s_size = 0;

    return s;
}

pstack pstack_push(pstack s,pstack_elem e,float average_grade,unsigned int approved_courses)
{
    assert(invrep(s));
    struct s_node *new_node = create_node(e, average_grade, approved_courses);
    struct s_node *current = s->front;
    struct s_node *bef_current = NULL;

    while (current != NULL && new_node->priority < current->priority)
    {
        bef_current = current;
        current = current->next;
    }

    if (bef_current == NULL)
    {
        new_node->next = current;
        s->front = new_node;
    }
    else
    {
        new_node->next = current;
        bef_current->next = new_node;
    }

    s->s_size = s->s_size + 1;
    assert(invrep(s));
    return s;
}

bool pstack_is_empty(pstack s) 
{
    return s->s_size == 0;
}

pstack_elem pstack_top(pstack s) 
{
    assert(invrep(s) && !pstack_is_empty(s));
    return s->front->elem;
}

float pstack_top_average_grade(pstack s) 
{
    assert(invrep(s));
    return s->front->average_grade;
}

unsigned int pstack_top_approved_courses(pstack s) 
{
    assert(invrep(s));
    return s->front->approved_courses;
}

float pstack_top_priority(pstack s) 
{
    assert(invrep(s));
   return s->front->priority;
}

unsigned int pstack_size(pstack s) 
{
    assert(invrep(s));
   
    return s->s_size;
}

pstack pstack_copy(pstack s)
{
    assert(invrep(s));
    pstack copied_s = pstack_empty();
    struct s_node *actual_index = s->front;
    struct s_node *act_index_cpy = NULL; // Variable para el nodo actual de la pila copiada

    while (actual_index != NULL)
    {
        // Creamos un nuevo nodo con los mismos valores
        struct s_node *new_node = create_node(actual_index->elem, actual_index->average_grade, actual_index->approved_courses);

        if (copied_s->front == NULL)
        {
            // Si la pila copiada está vacía, el nuevo nodo será el frente
            copied_s->front = new_node;
            act_index_cpy = copied_s->front;
        }
        else
        {
            // Enlazamos el nuevo nodo al nodo actual de la pila copiada
            act_index_cpy->next = new_node;
            act_index_cpy = act_index_cpy->next;
        }

        actual_index = actual_index->next;
    }
    copied_s->s_size = s->s_size;

    assert(invrep(copied_s));
    return copied_s;
}

pstack pstack_pop(pstack s) 
{
    assert(invrep(s));
    struct s_node *killme = s->front;

    s->front = s->front->next;
    killme = destroy_node(killme);
    s->s_size = s->s_size - 1;
    
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) 
{
    assert(invrep(s));
    struct s_node *killme = s->front;

    while(s->front != NULL)
    {
        killme = s->front;
        s->front = s->front->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    
    assert(s == NULL);
    return s;
}
