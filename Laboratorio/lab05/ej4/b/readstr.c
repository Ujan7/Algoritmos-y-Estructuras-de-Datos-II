#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

int main(void) 
{
    
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    fgets(user_input, MAX_LENGTH,stdin);

    size_t name_size = strlen(user_input);
    if (name_size > 0)
    {
        user_input[name_size - 1] = ' ';
    }

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}

