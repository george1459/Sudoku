#ifndef _BOARD_H
#define _BOARD_H

/* An allocation of a new board */
char** new_board();

/* Free an allocated board completely */
void free_board(char** board);

/* Print an allocated board, using | and - to denote blocks */
void print_board(char** board);

/* Read and return a board from an existing file */
char** read_board(char* filename);

/* If board contains elements of '.', change them all to zero */
void zeroize(char** board);

#endif /* _BOARD_H */
