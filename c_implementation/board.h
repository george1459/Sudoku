/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Shicheng Liu
#   Email         : shicheng2000@uchicago.edu
#   File Name     : board.h
#   Last Modified : 2019-07-15 16:44
#   Describe      :
#
# ====================================================*/

#ifndef _BOARD_H
#define _BOARD_H

/*
 *enum rep_type {
 *        ARRAY, BITS;
 *};
 *
 *union rep_board {
 *        char** array;
 *        char* bits;
 *};
 *
 *typedef union rep_board rep_board;
 *
 *struct board {
 *        rep_board r;
 *        enum rep_type t;
 *};
 *
 */
/*
 * If the bits type is required, all following array-like structures will also be represented with bits 
 */

/* An allocation of a new board */
char** new_board();

/* Free an allocated board completely */
void free_board(char** board);

/* Print an allocated board, using | and - to denote blocks */
void print_board(char** board);

/* Read and return a board from an existing file */
char** read_board(char* filename);

#endif /* _BOARD_H */
