#include "string.h"
#include <stdio.h>
int main()
{
    string str1 = string_create("cuatro");
    string str2 = string_create("dos");
    string str3 = string_create("banana");
    string str4 = string_create("banana");

    if (string_less(str1, str2))
    {
        printf("\nLa cadena 1 es mas grande que la cadena 2\n");
    }
    else
    {
        printf("\nLa cadena 2 es mas grande que la cadena 2\n");
    }

    if (string_eq(str3, str4))
    {
        printf("\nLas cadenas tienen la misma longitud\n");
    }
    else
    {
        printf("\nLas cadenas difieren en su longitud\n");
    }

    str1 = string_destroy(str1);
    str2 = string_destroy(str2);
    str3 = string_destroy(str3);
    str4 = string_destroy(str4);
    
    return 0;
}