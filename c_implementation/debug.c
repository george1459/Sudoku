/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Shicheng Liu
#   Email         : shicheng2000@uchicago.edu
#   File Name     : debug.c
#   Last Modified : 2019-07-14 23:07
#   Describe      : A debugger tool that displays logical outputs to help with understanding its performence
#
# ====================================================*/

# include <stdio.h>
# include <stdlib.h>
# include "logic.h"
# include "board.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Sudoku Debugger: Unable to parse input\nPlease revise your argument to include only the source file containing the Sudoku to be solved\nTo use the debugger functionality, please see README\n");
		exit(0);
	}
	char** res = workflow_debugger(argv[1]);
	free_board(res);
	return 1;
}
