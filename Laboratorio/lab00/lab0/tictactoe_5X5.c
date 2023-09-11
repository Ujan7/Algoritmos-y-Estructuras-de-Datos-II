#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */
#define BOARD_SIZE 5 /*Creo la constante para elegir el size del tablero*/

#define CELL_MAX (BOARD_SIZE * BOARD_SIZE - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    int cell = 0;

    print_sep(BOARD_SIZE);
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int column = 0; column < BOARD_SIZE; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(BOARD_SIZE);
    }
}

char get_winner(char board[BOARD_SIZE][BOARD_SIZE])
{
    char winner = '-';
    for (unsigned int i = 0; i < BOARD_SIZE; i ++) {
      if (board[0][i] == board[1][i] && board[2][i] == board[0][1] && (board[0][i] == 'X' || board[0][i] == 'O')) {
        winner = board[0][i];
      }

      if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && (board[i][0] == 'X' || board[i][0] == 'O')) {
        winner = board[i][0];
      }

      if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && (board[0][0] == 'X' || board[0][0] == 'O')) {
        winner = board[0][0];
      }

       if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && (board[0][2] == 'X' || board[0][2] == 'O')) {
        winner = board[0][2];
      }
    }
    
    return winner;
}

bool has_free_cell(char board[BOARD_SIZE][BOARD_SIZE])
{
    bool free_cell = false;
    for (unsigned int i = 0; free_cell != true && i < BOARD_SIZE; i ++) {
        for (unsigned int j = 0; free_cell != true && j < BOARD_SIZE; j++) {
            if (board[i][j] == '-') {
                free_cell = true;
            }
        }

    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[BOARD_SIZE][BOARD_SIZE] = {
        { '-', '-', '-' },
        { '-', '-', '-' },
        { '-', '-', '-' }
    };

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / BOARD_SIZE;
            int colum = cell % BOARD_SIZE;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}
