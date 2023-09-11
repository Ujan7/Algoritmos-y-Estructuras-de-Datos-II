#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"

unsigned int fstring_length(fixstring s) 
{
    unsigned int char_size = 0;
    for (unsigned int i = 0; s[i] != '\0'; i++) 
    {
        char_size ++;
    }
    return char_size;
}

bool fstring_eq(fixstring s1, fixstring s2) 
{
    bool are_eq = true;
    if (fstring_length(s1) != fstring_length(s2)) 
    {
        are_eq = false;
    } 
    else
    {
        for (unsigned int i = 0; s1[i] != '\0'; i++)
        {
            if (s1[i] != s2[i])
            {
                are_eq = false;
                break;
            }
        }
    }
    return are_eq;   
}

bool fstring_less_eq(fixstring s1, fixstring s2) 
{
    bool res = true;
    for (unsigned int i = 0; s1[i] != '\0'; i++ )
    {
        if (s1[i] > s2[i]) 
        {
            res = false;
            break;
        }
        else if (s1[i] < s2[i])
        {
            break;
        }
    }
    return res;
}

