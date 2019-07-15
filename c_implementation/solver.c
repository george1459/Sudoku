/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Shicheng Liu
#   Email         : shicheng2000@uchicago.edu
#   File Name     : solver.c
#   Last Modified : 2019-07-15 09:16
#   Describe      :
#
# ====================================================*/

# include <stdlib.h>
# include <stdio.h>
# include "logic.h"
# include "board.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Sudoku Solver: Unable to parse input\nPlease revise your argument to include only the source file containing the Sudoku to be solved\nTo use the debugger functionality, please see README\n");
		exit(0);
	}
	workflow(argv[1]);
	return 1;
}
