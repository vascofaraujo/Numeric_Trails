CC = gcc
CFLAGS = -Wall -std=c99 -O3


walker : walker.c problem.c problem.h readfile.c readfile.h list.c list.h macros.h
	gcc walker.c problem.c readfile.c list.c -o walker 
