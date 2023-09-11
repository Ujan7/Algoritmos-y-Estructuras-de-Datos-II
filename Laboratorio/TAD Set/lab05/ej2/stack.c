#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdio.h>
#include <stdbool.h>

#define CAPACITY 2

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

static bool invrep(stack s)
{
    if (s == NULL)
    {
        return false;
    }

    if (s->elems == NULL && s->size > 0)
    {
        return false;
    }
    if (s->size > s->capacity)
    {
        return false;
    }

    return true;
}

stack stack_empty()
{
    stack empty_s = malloc(sizeof(struct _s_stack));
    stack_elem *arr = malloc(CAPACITY *sizeof(stack_elem));
    
    empty_s->elems = arr;
    empty_s->size = 0;
    empty_s->capacity = CAPACITY;

    return empty_s;
}

stack stack_push(stack s, stack_elem e)
{
    assert(invrep(s));
    
    if (s->size == s->capacity)
    {
        s->capacity = 2 * s->capacity;
        s->elems = realloc(s->elems, s->capacity * sizeof(stack_elem));
    }
    
    s->elems[s->size] = e;
    s->size = s->size + 1;
    
    assert(invrep(s));
    return s;   
}

stack stack_pop(stack s)
{
    assert(invrep(s));
    
    s->size = s->size - 1;

    assert(invrep(s));
    return s;
}

unsigned int stack_size(stack s)
{
    assert(invrep(s));
    return s->size;
}

stack_elem stack_top(stack s)
{
    assert(!stack_is_empty(s));
    assert(invrep(s));
    
    return s->elems[s->size - 1];
}

bool stack_is_empty(stack s)
{
    assert(invrep(s));
    return s->size == 0;
}

stack_elem *stack_to_array(stack s)
{
    return s->elems;
}

stack stack_destroy(stack s)
{
    free(s->elems);
    free(s);

    return s;
}