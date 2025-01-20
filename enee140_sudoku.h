/*
 * enee140_sudoku.h
 *
 *  Contains function prototypes for the Sudoku library.
 */

#ifndef SUDOKU_H_
#define SUDOKU_H_

int is_valid_board(int board[9][9]);

void new_sudoku_board(int board[9][9], int blanks);

void transform_permute_rows(int board[9][9]);

void transform_permute_bands(int board[9][9]);

void transform_permute_columns(int board[9][9]);

void transform_permute_stacks(int board[9][9]);

void transform_flip_main_diagonal(int board[9][9]);

void transform_flip_minor_diagonal(int board[9][9]);

int print_sudoku_board(int board[9][9]);

int read_sudoku_board(const char file_name[], int board[9][9]);

int write_sudoku_board(const char file_name[], int board[9][9]);

int solve_sudoku_board(int board[9][9],int row,int col);//Bonus portion

int isZero(int board[][9], int row, int col, int num);//Function created for bonus portion

#endif /* SUDOKU_H_ */