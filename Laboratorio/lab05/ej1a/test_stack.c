#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include <stdio.h>

void array_dump(int a[], unsigned int length) 
{
    fprintf(stdout, "[");
    for (unsigned int i = 0u; i < length; ++i) 
    {
        fprintf(stdout, "%d", a[i]);
        if (i < length - 1) 
        {
            fprintf(stdout, ", ");
        } 
        else 
        {
            fprintf(stdout, "]\n");
        }
    }
}

int main()
{
    /*Creando la nueva pila s*/
    stack s = stack_empty();
    stack empty_s = stack_empty();
    
    /*Agregamos el elemento 5 al tope de la lista*/
    s = stack_push(s, 5);
    s = stack_pop(s);
    if (s == NULL) 
    {
        printf("\nEl pop funciona correctamente para pilas de size 1\n");
    }
    
    /*Chequeamos si esta vacia*/
    bool b = stack_is_empty(s);
    /*Generamos una salida para ver si la funcion trabaja correctamente*/
    if (b == 0)
    {
        printf("\nLuego de agregar el elemento 5 al tope de la lista, esta no esta vacia\n");
    }
    else
    {
        printf("\nLuego de agregar el elemento 5 al tope de la lista y haberlo quitado, esta esta vacia\n");
    }

    /*Agregamos el elemento 6 al tope de la lista*/
    s = stack_push(s, 6);
    /*Agregamos el elemento 7 al tope de la lista*/
    s = stack_push(s, 7);

    /*Obtenemos el size de la lista*/
    unsigned int s_size = stack_size(s);
    /*Generamos una salida para ver si la funcion trabaja correctamente*/
    printf("\nLuego de agregar 3 elementos al tope de la lista y haber quitado uno, el size es %d\n",s_size);

    /*Obtenemos el elemento que esta en el tope de la lista*/
    stack_elem top_s = stack_top(s);
    printf("\nEl elemento al tope de la lista es %d\n", top_s);

    /*Eliminamos el elemento al tope de la lista*/
    s = stack_pop(s);
    /*Generamos una salida para ver si la funcion trabaja correctamente*/
    unsigned int s_size2 = stack_size(s);
    printf("\nLuego de usar pop y haber eliminado el elemento que se encontraba en el tope de la pila (%d), el size de la lista es %d\n", top_s, s_size2);

    /*Generamos un arreglo a partir de la pila anterior*/
    int *array = stack_to_array(s);
    printf("\nEl arreglo resultante luego de haber convertido el stack (no vacio), es:\n");
    printf("\n");
    array_dump(array, s_size2);

    int *empty_array = stack_to_array(empty_s);
    if (empty_array == NULL)
    {
        printf("\nEl arreglo resultante luego de haber convertido el stack (vacio), es:\n");
        printf("\nNULL\n");
    }

    /*Luego de haber probado todas las funciones, procedemos a destruir la pila, para liberar posible memoria dinamica utilizada*/
    stack_destroy(s);
    stack_destroy(empty_s);
    free(array);
    return 0;
}