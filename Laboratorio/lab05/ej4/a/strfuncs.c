#include <stdio.h>
#include <stdlib.h>
#include "strfuncs.h"

size_t string_length(const char *str)
{
    size_t str_size = 0;
    for (unsigned int i = 0; str[i] != '\0'; i++)
    {
        str_size = str_size + 1;
    }

    return str_size;
}

char *string_filter(const char *str, char c)
{
    size_t index = 0;
    char filtered_string_size = 0;
        
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != c)
        {
            filtered_string_size = filtered_string_size + 1;
        }
    }
    
    char *filtered_string = (char *) malloc ((filtered_string_size + 1) * sizeof(char));
    
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != c)
        {
            filtered_string[index] = str[i];
            index = index + 1;
        }
    }
    
    filtered_string[index] = '\0';

    return filtered_string;

}