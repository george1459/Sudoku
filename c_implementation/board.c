/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Shicheng Liu
#   Email         : shicheng2000@uchicago.edu
#   File Name     : board.c
#   Last Modified : 2019-07-14 22:55
#   Describe      :
#
# ====================================================*/

# include <stdio.h>
# include <stdlib.h>


/* An allocation of board according to the given type */
char** new_board() {
	char** res = (char**)malloc(9 * sizeof(char*));
	unsigned int i, j;
	for (i = 0; i < 9; i ++) {
		char* temp = (char*)malloc(9 * sizeof(char));
		res[i] = temp;
	}
	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			res[i][j] = 0;
		}
	}
	return res;
}

void free_board(char** board) {
	unsigned int i;
	for (i = 0; i < 9; i ++) {
		free(board[i]);
	}
	free(board);
}

void print_board(char** board) {
	unsigned int i, j;
	for (i = 0; i < 9; i ++) {
		if (i % 3 == 0) {
			printf("\n");
		}
		for (j = 0; j < 9; j ++) {
			if (j % 3 == 0) {
				printf("   ");
			}
			printf("%c", board[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

char** read_board(char* filename) {
	FILE *fp;
	unsigned int i, j;
	char** board = new_board();
	fp = fopen(filename,"r");
	if (!fp) {
		fprintf(stderr, "file open error\n");
		exit(0);
	}
	for (i = 0; i < 9; i ++) {
		if (i % 3 == 0) {
			fscanf(fp, "\n");
		}
		for (j = 0; j < 9; j ++) {
			fscanf(fp, "%c", &board[i][j]);
			fscanf(fp, " ");
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
	return board;
}

void zeroize(char** board) {
	unsigned int i, j;
	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			if (board[i][j] == '.') {
				board[i][j] = '0';
			}
		}
	}
}
