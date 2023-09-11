#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdbool.h>

struct _s_stack
{
    stack_elem elem;
    struct _s_stack *next;
    unsigned int stack_size;
};

static bool invrep(stack s)
{
    if (s == NULL)
    {
        return false;
    }

    if (s->next == NULL && s->stack_size > 1)
    {
        return false;
    }

    return true;
}
 
stack stack_empty()
{
    stack s = malloc(sizeof(struct _s_stack));
    
    s->stack_size = 0;
    s->next = NULL;

    return s;
}

stack stack_push(stack s, stack_elem e)
{
    assert(invrep(s));
    
    stack new_node = malloc(sizeof(struct _s_stack));
    
    new_node->elem = e;
    new_node->next = s;
    new_node->stack_size = s->stack_size + 1;
    s = new_node;

    assert(invrep(s));
    return s;
}

stack stack_pop(stack s)
{
    assert(invrep(s));
    assert(!stack_is_empty(s));
    
    stack aux = s;

    s->stack_size = s->stack_size - 1;
    s = s->next;
    free(aux);

    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s) 
{
    return s->stack_size;
}

stack_elem stack_top(stack s)
{
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s)
{
    return s->stack_size == 0;
}

stack_elem *stack_to_array(stack s)
{
    assert(invrep(s));

    unsigned int s_size = stack_size(s);
    stack_elem *array = calloc(s_size, sizeof(struct _s_stack));
    stack s_aux = s;
    
    for (int i = s_size - 1; i >= 0; --i)
    {
        array[i] = stack_top(s_aux);
        s_aux = s_aux->next;
            
    }
    
    assert(invrep(s));
    return array;
   
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


