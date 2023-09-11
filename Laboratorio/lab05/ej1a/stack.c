#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack
{
    stack_elem elem;
    struct _s_stack *next;
};

 
stack stack_empty()
{
    return NULL;
}

stack stack_push(stack s, stack_elem e)
{
    stack new_node = malloc(sizeof(struct _s_stack));
    
    new_node->elem = e;
    new_node->next = s;
    s = new_node;

    return s;
}

stack stack_pop(stack s)
{
    if (!stack_is_empty(s))
    {
        stack aux = s;
        
        s = s->next;
        free(aux);
    }

    return s; 
}

unsigned int stack_size(stack s) 
{
    stack aux = s;
    unsigned int s_size = 0;
    
    while (aux != NULL)
    {
        aux = aux->next;
        s_size = s_size + 1;
    }

    return s_size;
}

stack_elem stack_top(stack s)
{
    assert(s != NULL);
    return s->elem;
}

bool stack_is_empty(stack s)
{
    return s == NULL;
}

stack_elem *stack_to_array(stack s)
{
    if (stack_is_empty(s)) 
    {
        return NULL;
    }
    else
    {
        unsigned int s_size = stack_size(s);
        stack_elem *array = calloc(s_size, sizeof(stack_elem));
        stack s_aux = s;
    
        for (int i = s_size - 1; i >= 0; --i)
        {
            array[i] = stack_top(s_aux);
            s_aux = s_aux->next;   
        }

        return array;
    }
}

stack stack_destroy(stack s)
{
    stack aux;
    
    while (!stack_is_empty(s))
    {
        aux = s;
        s = s->next;
        free(aux);
    }

    return s;
}


