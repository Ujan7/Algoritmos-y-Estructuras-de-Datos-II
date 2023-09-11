/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>
#include <stdlib.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};
    int *p = NULL;
    person_t *q = NULL;

    p = &x; /*El puntero ahora esta en la direccion de memoria de x*/
    *p = 9; /*El puntero asigna 9 a la direccion de memoria de x*/
    
    q = &m; /*El puntero de tipo person_t es un puntero a un nodo con dos campos, ahora esta en la direccion de memoria de m*/
    q->age = 100; /*Asigno "100" al campo "age" en la direccion de memoria de m*/
    q->name_initial = 'F'; /*Asigno "F" al campo "name_initial" en la direccion de memoria de m*/
    
    p = &a[1]; /*El puntero p ahora esta en la direccion de memoria del primer elemento del arreglo*/
    *p = 42; /*Asigno "42" en la direccion de memoria de a[1]*/

    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);

    return EXIT_SUCCESS;
}

