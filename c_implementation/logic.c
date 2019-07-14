/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Shicheng Liu
#   Email         : shicheng2000@uchicago.edu
#   File Name     : logic.c
#   Last Modified : 2019-07-14 22:55
#   Describe      :
#
# ====================================================*/

# include <stdio.h>
# include <stdlib.h>
# include "board.h"

# define L_GREEN "\e[1;32m"
# define BOLD "\e[1m"
# define NONE "\e[0m"
# define BLUE "\e[0;34m"

/* Allocate memory for all logcial parameters, indexed by [row, col, value] */
char*** new_parameters() {
	char*** res = (char***)malloc(9 * sizeof(char**));
	unsigned int i, j, k;
	for (i = 0; i < 9; i ++) {
		char** temp1 = (char**)malloc(9 * sizeof(char*));
		res[i] = temp1;
		for (j = 0; j < 9; j ++){
			char* temp2 = (char*)malloc(9 * sizeof(char));
			res[i][j] = temp2;
		}
	}
	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			for (k = 0; k < 9; k ++) {
				res[i][j][k] = 2;           /* 2 represents initial allocation. 1 represents true (asserted) while 0 represents false (denied) */
			}
		}
	}
	return res;
}

void free_parameters(char*** para) {
	unsigned int i, j;
	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			free(para[i][j]);
		}
		free(para[i]);
	}
	free(para);
}

/* new_logic is a 324*9 dimension matrix, each value is a pointer to a location at parameters */
char*** new_logic(char*** para) {
	char*** res = (char***)malloc(324 * sizeof(char**));
	unsigned int i, j, k, m, n;
	for (i = 0; i < 324; i ++) {
		res[i] = (char**)malloc(9 * sizeof(char*));
	}
	/* assert location logic */
	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			/*printf("AT LINE %d: ", i*9+j);*/
			for (k = 0; k < 9; k ++) {
				res[i * 9 + j][k] = &para[i][j][k];
				/*printf("%d%d%d ",i,j,k);*/
			}
			/*printf("\n");*/
		}
	}
	/* assert column logic */
	for (i = 0; i < 9; i ++) {
		for (k = 0; k < 9; k ++) {	
			/*printf("AT LINE %d: ", i*9+k+81);*/
			for (j = 0; j < 9; j ++) {
				res[i * 9 + k + 81][j] = &para[i][j][k];	
				/*printf("%d%d%d ",i,j,k);*/
			}
			/*printf("\n");*/
		}
	}
	/* assert row logic */
	for (j = 0; j < 9; j ++) {
		for (k = 0; k < 9; k ++) {	
			/*printf("AT LINE %d: ", j*9+k+162);*/
			for (i = 0; i < 9; i ++) {
				res[j * 9 + k + 162][i] = &para[i][j][k];
				/*printf("%d%d%d ",i,j,k);*/
			}
			/*printf("\n");*/
		}
	}
	/* assert block logic */
	for (m = 0; m < 3; m ++) {
		for (n = 0; n < 3; n ++) {
			for (k = 0; k < 9; k ++) {
				/*printf("AT LINE %d: ", m*27+n*9+k+243);*/
				for (i = 0; i < 3; i ++) {
					for (j = 0; j < 3; j ++) {
						res[m * 27 + n * 9 + k + 243][i * 3 + j] = &para[m * 3 + i][n * 3 + j][k];
						/*printf("%d%d%d ",m*3+i,n*3+j,k);*/
					}
				}
				/*printf("\n");*/
			}
			/*printf("\n");*/
		}
	}
	return res;
}

void free_logic(char*** logic) {
	unsigned int i;
	for (i = 0; i < 324; i ++) {
		free(logic[i]);
	}
	free(logic);
}


/* Empty declaration */
void check_denials(char*** logic, char*** to_assert, unsigned int* to_assert_len, char*** to_deny, unsigned int* to_deny_len);

int check_all_zero(char** logic, char interest) {
	unsigned int i; char check = 0;
	for (i = 0; i < interest; i ++) {
		check += *(logic[i]);
	}
	if (interest == 8) {
		return check;
	}
	for (i = interest + 1; i < 9; i ++) {
		check += *(logic[i]);
	}
	return check;
}


/* Preparation works done. Logic comes in */
/* to_assert is an array of pointers, each pointer points towards one location at parameter that needs to be asserted, passed in as out-parameter */
/* Same for to_deny and to_deny_len. */
/* Only logic is passed in as a passed-in value */
void check_asserts(char*** logic, char*** to_assert, unsigned int* to_assert_len, char*** to_deny, unsigned int* to_deny_len) {
	unsigned int i, j, k, n = 0;
	for (i = 0; i < (*to_assert_len); i ++) {
		*((*to_assert)[i]) = 1;
	}
	for (i = 0; i < 324; i ++) {
		for (j = 0; j < 9; j ++) {
			if (*(logic[i][j]) == 1 && check_all_zero(logic[i], j) != 0 ) {
				for (k = 0; k < j; k ++) {
					(*to_deny)[n] = logic[i][k];
					n ++;
				}
				for (k = j + 1; k < 9; k ++) {
					(*to_deny)[n] = logic[i][k];
					n ++;
				}
				j = 9;
			} 
		}
	}
	*to_deny_len = n;
	if (n != 0) {
		check_denials(logic, to_assert, to_deny_len, to_deny, to_deny_len);
	}
}

void check_denials(char*** logic, char*** to_assert, unsigned int* to_assert_len, char*** to_deny, unsigned int* to_deny_len) {
	unsigned int i, j, n = 0; char checker = 0;
	for (i = 0; i < (*to_deny_len); i ++) {
		*((*to_deny)[i]) = 0;
	}
	for (i = 0; i < 324; i ++) {
		for (j = 0; j < 9; j ++) {
			checker += *(logic[i][j]);
		}
		/* Check if only one parameter within one logic line has value two. If true, assert that particular parameter */
		if (checker == 2) {
			for (j = 0; j < 9; j ++) {
				if (*(logic[i][j]) == 2) {
					(*to_assert)[n] = logic[i][j];
					n ++;
				}
			}
		}
		checker = 0;	
	}
	*to_assert_len = n;
	if (n != 0) {
		check_asserts(logic, to_assert, to_deny_len, to_deny, to_deny_len);
	}
}

void print_logic(char*** logic) {
	printf("*** Now printing the logic output. Lines not asserted are highlighted with color\n*** The corresponding indices are in the order of: row, column, value\n");
	
	unsigned int i, j, k, m, n;
	/* Stores the logic table as a 2-dimensional array, indexed by the same line number */
	unsigned int** res = (unsigned int**)malloc(sizeof(unsigned int*) * 324);
	for (i = 0; i < 324; i ++) {
		res[i] = (unsigned int*)malloc(sizeof(unsigned int*) * 9);
	}
	
	/* assert location logic */
	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			for (k = 0; k < 9; k ++) {
				res[i * 9 + j][k] = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
			}
		}
	}
	/* assert column logic */
	for (i = 0; i < 9; i ++) {
		for (k = 0; k < 9; k ++) {
			for (j = 0; j < 9; j ++) {
				res[i * 9 + k + 81][j] = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
			}
		}
	}
	/* assert row logic */
	for (j = 0; j < 9; j ++) {
		for (k = 0; k < 9; k ++) {	
			for (i = 0; i < 9; i ++) {
				res[j * 9 + k + 162][i] = (i + 1) * 100 + (j + 1) * 10 + (k + 1);
			}
		}
	}
	/* assert block logic */
	for (m = 0; m < 3; m ++) {
		for (n = 0; n < 3; n ++) {
			for (k = 0; k < 9; k ++) {
				for (i = 0; i < 3; i ++) {
					for (j = 0; j < 3; j ++) {
						res[m * 27 + n * 9 + k + 243][i * 3 + j] = (m * 3 + i + 1) * 100 + (n * 3 + j + 1) * 10 + (k + 1);
					}
				}
			}
		}
	}

	for (i = 0; i < 324; i ++) {
		/* Check if this line is asserted, if asserted, only display its content in normal color */ 
		unsigned int checker = 0;
		for (j = 0; j < 9; j ++) {
			checker += *(logic[i][j]);
		}
		if (checker == 1) {
			printf(BLUE "LINE NUMBER %d:" NONE, i);
			for (j = 0; j < 9; j ++) {
				printf(BLUE "%c" NONE, *(logic[i][j]) + 48);
			}
			printf("\n");
		}
		else {
			printf(L_GREEN "LINE NUMBER %d:", i);
			for (j = 0; j < 9; j ++) {
				printf(L_GREEN "%c" NONE, *(logic[i][j]) + 48);
			}
			printf("  =>  ");
			for (j = 0; j < 9; j ++) {
				printf(BOLD "%d " NONE, res[i][j]);
			}
			printf("\n");
		}
		checker = 0;
	}

	for (i = 0; i < 324; i ++) {
		free(res[i]);
	}

	free(res);
}


int check_all_asserted(char*** logic) {
	unsigned int i, j, checker = 0;
	for (i = 0; i < 324; i ++) {
		for (j = 0; j < 9; j ++) {
			checker += *(logic[i][j]);
		}
		if (checker != 1) {
			return 0;
		}
		checker = 0;
	}
	return 1;
}

char** workflow(char* filename) {
	char** board = read_board(filename);
	
	printf("Here's the original problem:\n");
	print_board(board);

	unsigned int to_deny_len, to_assert_len = 0, i, j, k;	
	char*** para = new_parameters();
	char*** logic = new_logic(para);
	char*** to_assert = (char***)malloc(sizeof(char**));
	char*** to_deny = (char***)malloc(sizeof(char**));
	*to_deny = (char**)malloc(2916 * sizeof(char*));
	*to_assert = (char**)malloc(324 * sizeof(char*));
	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			switch(board[i][j]) {
				case '1':
					(*to_assert)[to_assert_len] = &para[i][j][0];
					to_assert_len ++;
					break;
				case '2':
					(*to_assert)[to_assert_len] = &para[i][j][1];
					to_assert_len ++;
					break;
				case '3':
					(*to_assert)[to_assert_len] = &para[i][j][2];
					to_assert_len ++;
					break;
				case '4':
					(*to_assert)[to_assert_len] = &para[i][j][3];
					to_assert_len ++;
					break;
				case '5':
					(*to_assert)[to_assert_len] = &para[i][j][4];
					to_assert_len ++;
					break;
				case '6':
					(*to_assert)[to_assert_len] = &para[i][j][5];
					to_assert_len ++;
					break;
				case '7':
					(*to_assert)[to_assert_len] = &para[i][j][6];
					to_assert_len ++;
					break;
				case '8':
					(*to_assert)[to_assert_len] = &para[i][j][7];
					to_assert_len ++;
					break;
				case '9':
					(*to_assert)[to_assert_len] = &para[i][j][8];
					to_assert_len ++;
					break;
			}

		}
	}

	check_asserts(logic, to_assert, &to_assert_len, to_deny, &to_deny_len);

	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			for (k = 0; k < 9; k ++) {
				if (para[i][j][k] == 1) {
					board[i][j] = k + 48 + 1;
				}
			}
		}
	}

	if (check_all_asserted(logic)) {
		printf("\nAll logic asserted. Problem solved:\n");
	}
	
	else {
		printf("\nNot all logic asserted. Problem under-solved:\n");
	}

	free_logic(logic);
	free_parameters(para);
	free(*to_deny);
	free(*to_assert);
	free(to_deny);
	free(to_assert);
	return board;
}

char** workflow_debugger(char* filename) {
	char** board = read_board(filename);
	
	printf("Here's the original problem:\n");
	print_board(board);

	unsigned int to_deny_len, to_assert_len = 0, i, j, k;	
	char*** para = new_parameters();
	char*** logic = new_logic(para);
	char*** to_assert = (char***)malloc(sizeof(char**));
	char*** to_deny = (char***)malloc(sizeof(char**));
	*to_deny = (char**)malloc(2916 * sizeof(char*));
	*to_assert = (char**)malloc(324 * sizeof(char*));
	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			switch(board[i][j]) {
				case '1':
					(*to_assert)[to_assert_len] = &para[i][j][0];
					to_assert_len ++;
					break;
				case '2':
					(*to_assert)[to_assert_len] = &para[i][j][1];
					to_assert_len ++;
					break;
				case '3':
					(*to_assert)[to_assert_len] = &para[i][j][2];
					to_assert_len ++;
					break;
				case '4':
					(*to_assert)[to_assert_len] = &para[i][j][3];
					to_assert_len ++;
					break;
				case '5':
					(*to_assert)[to_assert_len] = &para[i][j][4];
					to_assert_len ++;
					break;
				case '6':
					(*to_assert)[to_assert_len] = &para[i][j][5];
					to_assert_len ++;
					break;
				case '7':
					(*to_assert)[to_assert_len] = &para[i][j][6];
					to_assert_len ++;
					break;
				case '8':
					(*to_assert)[to_assert_len] = &para[i][j][7];
					to_assert_len ++;
					break;
				case '9':
					(*to_assert)[to_assert_len] = &para[i][j][8];
					to_assert_len ++;
					break;
			}

		}
	}

	check_asserts(logic, to_assert, &to_assert_len, to_deny, &to_deny_len);

	for (i = 0; i < 9; i ++) {
		for (j = 0; j < 9; j ++) {
			for (k = 0; k < 9; k ++) {
				if (para[i][j][k] == 1) {
					board[i][j] = k + 48 + 1;
				}
			}
		}
	}

	if (check_all_asserted(logic)) {
		printf("\nAll logic asserted. Problem solved:\n");
	}
	
	else {
		printf("\nNot all logic asserted. Problem under-solved:\n");
	}
	
	print_board(board);
	print_logic(logic);

	free_logic(logic);
	free_parameters(para);
	free(*to_deny);
	free(*to_assert);
	free(to_deny);
	free(to_assert);
	return board;
}
