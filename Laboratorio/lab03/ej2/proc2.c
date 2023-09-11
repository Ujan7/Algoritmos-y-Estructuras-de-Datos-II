#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int *y) 
{
    if (x >= 0) 
    {
        *y = x; /*Como es positivo el valor de x, modifico el valor del puntero en la direccion de memoria de x*/
    }
    else
    {
        *y = -x; /*Como es negativo el valor de x, modifico el valor del puntero en la direccion de memoria de x*/
    }
}


int main(void) 
{
    int a = 0, res = 0;  // No modificar esta declaración
    int *pointer = NULL;
    
    a = -10;
    pointer = &res;
   
    absolute(a,pointer); 
    printf("%d\n",res);
    
    return EXIT_SUCCESS;
}

