#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"
#include "fixstring.h"


static unsigned int partition(fixstring a[], unsigned int izq, unsigned int der) 
{
    unsigned int i = izq + 1;
    unsigned int j = der;
    unsigned int pivot = izq;
    while (i <= j) 
    {
       if (goes_before(a[pivot],a[i]) && goes_before(a[j],a[pivot]))
       {
        swap(a,i,j);
       }
       else
       {
        if (goes_before(a[i],a[pivot]))
        {
            i++;
        }
        if (goes_before(a[pivot],a[j]))
        {
            j--;
        }
       }
    }
    swap(a,pivot,j);
    return pivot = j; 
}

static void quick_sort_rec(fixstring a[], unsigned int izq, unsigned int der) 
{
    if (izq < der)
    {
        unsigned int pivot = partition(a,izq,der);
        if (pivot > izq)
        {
            quick_sort_rec(a,izq,pivot - 1);
            quick_sort_rec(a,pivot + 1, der); 
        }
        else
        {
            quick_sort_rec(a,izq,pivot);
            quick_sort_rec(a,pivot + 1, der); 
        }
    }
}

void quick_sort(fixstring a[], unsigned int length) 
{
    quick_sort_rec(a, 0u, (length == 0u) ? 0u: length - 1u);
}


