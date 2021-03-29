#include <stdio.h>
#include <stdlib.h> 
#include <string.h>  
#include "problem.h"

void openFile(FILE **fp, char *argv[]);
void openFileOut(FILE **fs, char *argv[]);
int testeEntries(tProblema *novoP);
void readFile(FILE **fp, int *numProblema);
void allocateMatrix(tProblema *novoP, int linhasA, int colunasA);
void menu();
void printPath(FILE **fs);


