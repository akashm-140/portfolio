/*
 * enee140_sudoku.c
 *
 * Implementation of the Sudoku library.
 *
 */

#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Check that the board is valid: each number between 1 and 9 must appear only
// once in each row, column and 3 x 3 box in the board. The board may include
// blank elements.

/* Return 0 if it is not a valid board */
/* Four things to check:
 * 1. Each cell holds a number 1-9 - COMPLETED
 * 2. No number is repeated in any row - COMPLETED
 * 3. No number is repeated in any column - COMPLETED
 * 4. No number is repeated in any box - COMPLETED
 */

int is_valid_board(int board[9][9]) {//First [9] is row number and second [9] is column number
    int i,j,k;

    //These nested for loops make sure only numbers 1-9 are in each position on the board
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(board[i][j]>9 || board[i][j]<0){
                printf("Error: Invalid sudoku board detected.\n");
            }else{
                continue;
            }
        }
    }

    //These nested for loops make sure no number is repeated in any row or column
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            for(k=j+1;k<9;k++){
                if (board[i][j] == board[i][k] && (board[i][j] != 0 && board[i][k] != 0)) {//In same row, if 2 column numbers are the same
                    printf("Error: Invalid sudoku board detected.\n");
                    return 0;
                }
                if (board[j][i] == board[k][i] && (board[j][i] != 0 && board[k][i] != 0)){//In same column, if 2 row numbers are the same
                    printf("Error: Invalid sudoku board detected.\n");
                    return 0;
                }
            }
        }
    }

    int idx;
    int a,b;
    int array[9];
    for(i=0;i<9;i++){
        idx=0;
        for(j=(i/3)*3;j<((i/3)*3)+3;j++){
            for(k=(i%3)*3;k<((i%3)*3)+3;k++){
                array[idx] = board[j][k];
            }
        }
        for(a=0;a<9;a++){
            for(b=0;b<a;b++){
                if(array[a]==array[b]){
                    return 0;
                }
            }
        }
    }
    return 1;
}


//Generates a valid sudoku board
void new_sudoku_board(int board[9][9], int blanks) {
    int canonical_board[9][9] =
            {{1, 2, 3, 4, 5, 6, 7, 8, 9},
             {4, 5, 6, 7, 8, 9, 1, 2, 3},
             {7, 8, 9, 1, 2, 3, 4, 5, 6},
             {2, 3, 4, 5, 6, 7, 8, 9, 1},
             {5, 6, 7, 8, 9, 1, 2, 3, 4},
             {8, 9, 1, 2, 3, 4, 5, 6, 7},
             {3, 4, 5, 6, 7, 8, 9, 1, 2},
             {6, 7, 8, 9, 1, 2, 3, 4, 5},
             {9, 1, 2, 3, 4, 5, 6, 7, 8}};


    int i; //Row
    int j; //Column
    for (i = 0; i<9; i++) {
        for (j = 0; j<9; j++) {
            board[i][j] = canonical_board[i][j];
        }
    }
    for(int x = 0; x<blanks; x++) {//Choosing random row values and column values to blank out
        i = rand() % 9; //row
        j = rand() % 9; //column
        while(board[i][j] == 0) {
            i = rand() % 9; //row
            j = rand() % 9; //column
        }
        board[i][j] = 0; //Blank those values out
    }
}

void transform_permute_rows(int board[9][9]) {//Altering rows in board
    int initial_1 = rand() % 3 ; // for upper band index varies from 0 to 2.
    int final_1 = rand() % 3 ;

    int initial_2 = 3 + rand() % 3 ; //for middle band index varies from 3 to 5.
    int final_2 = 3 + rand() % 3 ;

    int initial_3 = 6 + rand() % 3 ; //for lower band index varies from 6 to 8.
    int final_3 = 6 + rand() % 3 ;

    int temp, i;

// Permuting rows in upper band.
    for(i = 0; i < 9; i ++){
        temp = board[initial_1][i];
        board[initial_1][i] = board[final_1][i];
        board[final_1][i] = temp;
    }

// Permuting rows in middle band.
    for(i = 0; i < 9; i ++){
        temp = board[initial_2][i];
        board[initial_2][i] = board[final_2][i];
        board[final_2][i] = temp;
    }

// Permuting rows in lower band.
    for(i = 0; i < 9; i ++){
        temp = board[initial_3][i];
        board[initial_3][i] = board[final_3][i];
        board[final_3][i] = temp;
    }
}

void transform_permute_bands(int board[9][9]) {//Altering bands in board
    int random_band1 = rand()%3;
    int random_band2 = rand()%3;
    int tmp,i,j;
    if (random_band1 == random_band2){
        random_band2 = rand()%3;
    }
    int start1 = 0 + random_band1 * 3;
    int start2 = 0 + random_band2 * 3;
    for (i=start1;i<start1+3;i++){
        for (j=0;j<9;j++) {
            tmp = board[i][j];
            board[i][j] = board[start2][j];
            board[start2][j] = tmp;
        }
        start2++;
    }
}

void transform_permute_columns(int board[9][9]) {//Altering columns in board
    int initial_1 = rand() % 3 ; //For upper band index varies from 0 to 2.
    int final_1 = rand() % 3 ;

    int initial_2 = 3 + rand() % 3 ; //For middle band index varies from 3 to 5.
    int final_2 = 3 + rand() % 3 ;

    int initial_3 = 6 + rand() % 3 ; //For lower band index varies from 6 to 8.
    int final_3 = 6 + rand() % 3 ;

    int temp, j;

// permuting rows in upper band.
    for(j = 0; j < 9; j ++){
        temp = board[j][initial_1];
        board[j][initial_1] = board[j][final_1];
        board[j][final_1] = temp;
    }

// permuting rows in middle band.
    for(j = 0; j < 9; j ++){
        temp = board[j][initial_2];
        board[j][initial_2] = board[j][final_2];
        board[j][final_2] = temp;
    }

// permuting rows in lower band.
    for(j = 0; j < 9; j ++){
        temp = board[j][initial_3];
        board[j][initial_3] = board[j][final_3];
        board[j][final_3] = temp;
    }
}

void transform_permute_stacks(int board[9][9]) {//Altering stacks in board
    int random_stack1 = rand()%3;
    int random_stack2 = rand()%3;
    int tmp,i,j;
    if(random_stack1 == random_stack2){
        random_stack2 = rand()%3;
    }
    int start1 = 0 + random_stack1 * 3;
    int start2 = 0 + random_stack2 * 3;
    for(i=start1;i<start1+3;i++){
        for(j=0;j<9;j++) {
            tmp = board[j][i];
            board[j][i] = board[j][start2];
            board[j][start2] = tmp;
        }
        start2++;
    }
}

void transform_flip_main_diagonal(int board[9][9]) {//Flips along primary diagonal
    int i,j,temp[9][9];

    for(i=0;i<9;i++) {
        for(j=0;j<9;j++) {
            temp[i][j] = board[i][j];
        }
    }
    for(i=0;i<9;i++) {
        for(j=0;j<9;j++) {
            board[i][j] = temp[j][i];
        }
    }
}

void transform_flip_minor_diagonal(int board[9][9]) {//Flips along secondary diagonal
    int i, j, temp;

    // Loops till number of rows
    for(i = 0; i < 8; i++) {
        // Loops from 0 to length of the row minus outer loop value
        for(j = 0; j < 8 - i; j++) {
            // Swap elements above anti-diagonal with elements below it
            temp = board[i][j];
            board[i][j] = board[8 - j][8 - i];
            board[8 - j][8 - i] = temp;
        }
    }
}

int print_sudoku_board(int board[9][9]) {//Prints the board
    int i,j;
    for(i=0; i<9; i++) {
        for (j = 0; j < 9; j++) {
            if(board[i][j] > 9 || board[i][j] < 0) {
                return -1;
            }
        }
    }

    for(i=0; i<9; i++) {//Generating walls of board
        if(i%3 == 0) {
            printf("+---------+---------+---------+\n");
        }
        for(j=0; j<9; j++) {
            if(j%3 == 0) {
                printf("|"); //Prints board walls
            }
            if(board[i][j] == 0) {
                printf(" - "); //Switches zeroes to - for proper design
            } else {
                printf(" %d ", board[i][j]);
            }
        }
        printf("|\n");
    }
    printf("+---------+---------+---------+\n");//Prints e
    return 0;
}

int read_sudoku_board(const char file_name[], int board[9][9]) {//Read board
    /*This function should read a Sudoku board from a file, in the format described in Step 13. Ignore
any characters after the 9th line in the file. The function should return 0 on success, -1 if any file
I/O error occurred, -2 if an invalid character (other than 1–9 and -) was encountered and -3 if the
file format is invalid (e.g. not enough lines or lines too short)*/

    char line[11];
    int i,j;

    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        printf("File could not be opened.");
        return -1;
    }

    for (i=0;i<9;i++) {
        if (fgets(line,12,file) != NULL) {
            for (j=0;j<9;j++) {
                if (line[j] == '-') {//Switches - to a 0 for code to properly work
                    int value = 0;
                    board[i][j] = value;
                } else if (line[j] > '9' || line[j] < '1') {
                    fclose(file);
                    return -2;
                } else {
                    int value = line[j] - '0';
                    board[i][j] = value;
                }
            }
        } else {
            fclose(file);
            return -3;
        }
    }
    fclose(file);
    return 0;
}

int write_sudoku_board(const char file_name[], int board[9][9]) {
    /*This function should save the board to a file. The function should return 0 on success, -1 if any
file I/O error occurred and -2 if an invalid board was provided. In the output file, write a line for
each row, with no spaces, and use a dash (the '-' character) to represent blanks. For example,
the Sudoku board on page 2 should be saved as follows:
 */
    FILE *file = fopen(file_name,"w");

    if (file == NULL) {
        printf("Error detected with File I/O.");
        return -1;
    }

    int i,j;

    if ((is_valid_board(board))) {
        printf("Error: Invalid sudoku board detected.\n");
        return -2;
    }
    for (i=0; i<9; i++) {
        for (j = 0; j < 9; j++) {
            if (board[i][j]==0) {
                fprintf(file,"-");
            } else {
                fprintf(file,"%d",board[i][j]);
            }
        }
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}