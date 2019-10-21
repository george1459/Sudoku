/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Shicheng Liu
#   Email         : shicheng2000@uchicago.edu
#   File Name     : logic.h
#   Last Modified : 2019-07-15 09:16
#   Describe      :
#
# ====================================================*/


#ifndef _LOGIC_H
#define _LOGIC_H

/* The main workflow given a particular file */
void workflow(char* filename);

/* The main workflow in debugger mode given a particular file */
void workflow_debugger(char* filename);

/* Allocate memory for all logcial parameters, indexed by [row, col, value] */
//char*** new_parameters();

/* Free the allocated parameters */
//void free_parameters(char*** para);

/* new_logic is a 324*9 dimension matrix, each value is a pointer to a location at parameters. It aalso asserts the corresponding logical list */
//char*** new_logic(char*** para);

/* Free up the allocated logic matrix */
//void free_logic(char*** logic);

/* Main logic work done through this mutual recursion */
//void check_denials(char*** logic, char*** to_assert, unsigned int* to_assert_len, char*** to_deny, unsigned int* to_deny_len);
 
/* Main logic work done through this mutual recursion */
//void check_denials(char*** logic, char*** to_assert, unsigned int* to_assert_len, char*** to_deny, unsigned int* to_deny_len);

/* Print the 324 lines of logical statements */
//void print_logic(char*** logic);

/* Check if a given logic list is all-asserted */
//int check_all_asserted(char*** logic);

#endif /* _LOGIC_H */
