// enee140_solve_sudoku.c
// Solve the sudoku board - BONUS

#include "enee140_sudoku.h"

int solve_sudoku_board(int board[9][9], int row, int col) {
    int i;
    if (row < 9 && col < 9) {//If it is a solid, valid board
        if (board[row][col] != 0){//If the number isn't 0
            if ((col+1) < 9) {
                return solve_sudoku_board(board,row,col+1);
            } else if ((row+1) < 9) {
                return solve_sudoku_board(board,row + 1,0);
            } else {
                return 1;
            }
        } else {//If the number is zero
            for (i = 0; i < 9; i++) {//The many loops here drop numbers to find possible solutions - backtracking 101
                if (isZero(board, row, col, i + 1)) {
                    board[row][col] = i + 1;
                    if ((col+1) < 9) {
                        if(solve_sudoku_board(board,row,col + 1)) {
                            return 1;
                        } else {
                            board[row][col] = 0;
                        }
                    } else if ((row+1) < 9) {
                        if (solve_sudoku_board(board,row + 1,0)) {
                            return 1;
                        } else {
                            board[row][col] = 0;
                        }
                    } else {
                        return 1;
                    }
                }
            }
        }
        return 0;
    } else {
        return 1;
    }
}

int isZero(int board[][9], int row, int col, int num) { // Reads in sudoku board values for available values - Helper function for solving sudoku
    int rowBegin = (row/3) * 3;
    int colBegin = (col/3) * 3;
    int i;
    for (i = 0; i < 9; ++i) {
        if (board[row][i] == num) { // If there is a number in that box, move on (check columns)
            return 0;
        }
        if (board[i][col] == num) { // If there is a number in that box, move on (check columns)
            return 0;
        }
        if (board[rowBegin + (i % 3)][colBegin + (i/3)] == num) { // Check in each box
            return 0;
        }
    }
    return 1;
}