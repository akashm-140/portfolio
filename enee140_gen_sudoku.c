/*
* enee140_gen_sudoku.c
*
* Generate Sudoku boards.
*
*/

#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int board[9][9];
    int options = atoi(argv[2]);
    int diff = 0;

    if (argc <= 2) {
        printf("Error: Insufficient arguments entered.\n");
        return 0;
    }

    time_t t;
    srand(time(&t));

    if (argc == 4) {//Checks for proper arguments - Detects if there is a difficulty required
        //Generating the difficulty level board (i.e. hard board has many blanks)
        if (strcmp(argv[3], "easy")) {
            diff = 31 + (rand() % 15);
        } else if (strcmp(argv[3], "medium")) {
            diff = 46 + (rand() % 6);
        } else if (strcmp(argv[3], "hard")) {
            diff = 52 + (rand() % 10);
        }
    }

    printf("Sudoku Board(If Requested): \n");
    // Interpret the options argument
    if ((options) & 1) { // Read - Generate the board provided
        if (read_sudoku_board(argv[1], board) != 0) { // Read in the board
            return 0;
        }
    } else {//No board provided - Create a new one
        if (diff != 0) { // If there is a difficulty, change the board to have that level
            new_sudoku_board(board, diff);
        } else { // Print normal board
            new_sudoku_board(board, 31 + (rand() % 31));
        }
    }

    //Logic for the options - your input determines what happens
    if ((options >> 1) & 1) {
        transform_permute_rows(board);
    }
    if ((options >> 2) & 1) {
        transform_permute_bands(board);
    }
    if ((options >> 3) & 1) {
        transform_permute_columns(board);
    }
    if ((options >> 4) & 1) {
        transform_permute_stacks(board);
    }
    if ((options >> 5) & 1) {
        transform_flip_main_diagonal(board);
    }
    if ((options >> 6) & 1) {
        transform_flip_minor_diagonal(board);
    }
    if ((options >> 7) & 1) {
        print_sudoku_board(board);
    }
    if ((options >> 8) & 1) {
        write_sudoku_board(argv[1],board);
    }

    //Solver - BONUS
    int i,j;
    printf("\nSolved Sudoku Board: \n");
    if (solve_sudoku_board(board,0,0)) {//Blank checker
        for (i = 0; i < 9; i++) {
            if (i % 3 == 0) { //Prints divider after every band
                printf("+---------+---------+---------+\n");
            }
            for (j = 0; j < 9; j++) {
                if (j % 3 == 0) { //Prints the divider
                    printf("|");
                }

                if (board[i][j] == 0) { //Prints - for every blank
                    printf(" - ");
                } else { // Prints number in board
                    printf(" %d ", board[i][j]);
                }
            }
            printf("|\n");
        }
        printf("+---------+---------+---------+\n");
    } else {//Assuming the board is impossible difficulty
        printf("Error: Unsolvable board was detected. Solvable board required.");
    }
    return 0;
}