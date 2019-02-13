cmake_minimum_required(VERSION 3.13)
project(SAT_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(SAT_2 source/main.c source/Clause.c head/Clause.h source/LiteralList.c head/LiteralList.h source/Literal.c head/Literal.h source/ClauseList.c head/ClauseList.h source/ClauseMap.c head/ClauseMap.h source/SAT.c head/SAT.h source/DPLL.c head/DPLL.h source/MyStack.c head/MyStack.h source/Sudoku.c head/Sudoku.h)