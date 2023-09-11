#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path,unsigned int indexes[],char letters[],unsigned int max_size)
{
    FILE *pointer = fopen(path,"r");
    unsigned int i = 0;
    max_size = MAX_SIZE;
    unsigned int size = 0;
    
    if (pointer == NULL)
    {
        printf("File doesn't exist\n");
        exit(EXIT_FAILURE);

    }
    while (!feof(pointer) && size <= max_size)
    {
        int res = fscanf(pointer,"%u -> *%c*\n",&indexes[i],&letters[i]);
        if (indexes[i] > max_size)
        {
            printf("Invalid index\n");
            exit(EXIT_FAILURE);
        }
        if (res != 2)
        {
            printf("Invalid format\n");
            exit(EXIT_FAILURE);
        }
        
        size ++;
        i++;
    }

    fclose(pointer);
    return size;
}

/*Creo una funcion tal que, teniendo ya los arreglos cargados de datos, acceda al array de los indices para saber donde va la letra en el arreglo que voy a devolver ordenado*/
void sorter_letters_a(char letters[],char sorted[],unsigned int indexes[],unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        unsigned int correct_index = indexes[i];
        sorted[correct_index] = letters[i];
    } 
}

int main(int argc, char *argv[]) 
{
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length = 0;

    length = data_from_file(argv[argc-1],indexes,letters,length); /*Obtengo length para saber hasta donde iterar la funcion sorter_letters_array*/
    sorter_letters_a(letters,sorted,indexes,length); /*Cargo en sorted los elementos de tipo char en su correspondiente indice*/
    dump(sorted, length);
    
    return EXIT_SUCCESS;
}
