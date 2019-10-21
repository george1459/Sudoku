#!/usr/bin/env python3
# encoding: utf-8
# coding style: pep8
# ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Shicheng Liu
#   Email         : shicheng2000@uchicago.edu
#   File Name     : board.py
#   Last Modified : 2019-07-16 08:59
#   Describe      :
#
# ====================================================

import sys
import os
import numpy as np


def new_board():
    a = np.zeros((9,13))
    return a


def print_board(board):
    for i in range(9):
        if (i % 3 == 0):
            print("\n");
        for j in range(9):
            if (j % 3 == 0):
                printf("   ")
            print("%c", board[i][j])
            print(" ")
            print("\n")


def read_board(filename):
    board = new_board()
    i = 0
    with open(filename, 'r') as fp:    
        for line in fp.readlines():
            if (i % 3 != 0):
                line_list = line.split(' ')
                board[i] = line_list
            i += 1
    return board

board = read_board("test.txt");
print_board(board);
