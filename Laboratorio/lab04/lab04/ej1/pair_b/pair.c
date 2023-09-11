#include <stdlib.h>  
#include <stdio.h>   
#include "pair.h"    

pair_t pair_new(int x, int y)
{
    pair_t res = malloc (sizeof(struct s_pair_t));
    
    res->fst = x;
    res->snd = y;

    return res;
}

int pair_first(pair_t p)
{
    return p->fst;
}

int pair_second(pair_t p)
{
    return p->snd;
}

pair_t pair_swapped(pair_t p)
{
    pair_t pSwapped = malloc(sizeof(struct s_pair_t));
    pSwapped->fst = p->snd;
    pSwapped->snd = p->fst;
    return pSwapped;
}

pair_t pair_destroy(pair_t p)
{
    free(p);
    return p;
}