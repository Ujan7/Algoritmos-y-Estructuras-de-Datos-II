#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    res.is_lowerbound = true;
    res.is_upperbound = true;
    res.exists = false;
    for (unsigned int i = 0; i < length; i ++) {
        
        if (value == arr[i] && res.exists == false) {
            res.exists = true;
            res.where = i;
        }

        if (value < arr[i]) {
            res.is_upperbound = false;
        }
        if (value > arr[i]) {
            res.is_lowerbound = false;
        }
    }
    return res;
}

int main(void) {
    int length;
    int value;

    printf("Ingrese un valor el cual desee comparar con los demas elementos del arreglo\n");
    scanf("%d",&value);

    printf ("Ahora ingrese el size del arreglo\n");
    scanf("%d",&length);

    int a[length];

    printf("Por ultimo ingrese los elementos del arreglo\n");
    for (int i = 0; i < length;i ++) {
        printf("Ingrese el valor en la posicion %d del arreglo\n",i);
        scanf("%d",&a[i]);
    }

    struct bound_data result = check_bound(value,a,length);

    if (result.exists == true) {
        
        if (result.is_upperbound == true) {

            printf("El valor ingresado es maximo de todos los elementos que componen al arreglo y su posicion es %d.\n",result.where);
        }
        if (result.is_lowerbound == true) {

            printf("El valor ingresado es minimo de todos los elementos que componen al arreglo y su posicion es %d\n",result.where);
        }
        if (result.is_lowerbound == false && result.is_upperbound == false) {
            printf("El resultado ingresado forma parte del arreglo, pero no es maximo ni minimo.\n");
        }
    }

    if (result.exists == false) {

        if (result.is_upperbound == true) {

            printf("El valor ingresado es cota superior de todos los elementos que componen al arreglo puesto que no forma parte del mismo.\n");  
        }
        if (result.is_lowerbound == true) {

            printf("El valor ingresado es cota inferior de todos los elementos que componen al arreglo puesto que no forma parte del mismo.\n");
        }
        if (result.is_lowerbound == false && result.is_upperbound == false) {
            printf("El resultado ingresado no forma parte del arreglo, y no es cota superior ni inferior.\n");
        }
    }

    return EXIT_SUCCESS;
}

