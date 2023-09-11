#include <stdlib.h>
#include <stdio.h>

void absolute(int x, int y) 
{
    if (x >= 0) 
    {
        y = x; /*Como es positivo el valor de x se mantiene*/
    }
    else
    {
        y = -x; /*Como es negativo el valor de x se modifica*/
    }
}

int main(void) 
{
    int a = 0, res = 0;  // No modificar esta declaración
    a = -10;
    absolute(a,res);
    printf("%d",res);
    return EXIT_SUCCESS;
   
}

/*El resultado no se corresponde al del teorico practico puesto que absolute1 es de
tipo void y solo modifica el valor de "y" en su modulo*/
 



