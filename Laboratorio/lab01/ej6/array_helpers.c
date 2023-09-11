#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    FILE *pointer = fopen(filepath, "r");
    int aux;
    unsigned int size;
    int res;
    
    if (pointer == NULL) {
        printf("No se pudo leer el archivo\n");
        exit(EXIT_FAILURE);
    }
    else {
        fscanf(pointer,"%u",&size);
        if (max_size < size) {
            size = max_size;
        }
        for (unsigned int i = 0; i < size; i++) {
            res = fscanf(pointer,"%d",&aux);
            if (res == EOF) {
                printf("Error, formato invalido\n");
                exit(EXIT_FAILURE);
            }
            array[i] = aux;
        }
    }
    
    fclose(pointer);
    return size;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    if (length > 0) {
        printf("%d",a[0]);
        for (unsigned int i = 1; i < length; i++) {
        printf(",%d",a[i]);
    }
    }
    printf("]\n");
}

bool array_is_sorted(int a[], unsigned int length) {
    bool a_is_sorted = true;
    for (unsigned int i = 0; i < (length - 1); i++) {
        if (a[i] > a[i + 1]) {
            a_is_sorted = false;
            break;
        }
    }
    return a_is_sorted;
}

void array_swap(int a[], unsigned int i, unsigned int j) {
    int var_aux = a[i];
    a[i] = a[j];
    a[j] = var_aux;
}

void reverse_a (int a[], unsigned int length) {
    unsigned int mid_position = (length / 2) + 1; /*quedo en la posicion que se mantiene igual*/
    for (unsigned int i = mid_position; i < length;i ++) {
        array_swap(a,(length - 1) - i,i);
    }
}


