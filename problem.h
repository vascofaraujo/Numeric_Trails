#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "list.h"

tProblema *problemAB(tProblema *No);
tProblema *problemCD(tProblema *No);
tProblema *createVisited(tProblema *No);
tProblema *solveProblemAC(tProblema *No, int linhaP, int colunaP, int *numPassosAux);
int visited(tProblema *No, int numPassos, int linha, int coluna);
tProblema *solveProblemBD(tProblema *No, int linhaP, int colunaP, int *numPassosAux);
tProblema *problemE(tProblema *No);
tProblema *createVisitedE(tProblema *No);
tProblema *createBiggestGlobalPath(tProblema *No);
tProblema *solveProblemE(tProblema *No, int linhaP, int colunaP, int *numPassosAux, int *maiorNumPassos, int *maiorCaminho);
tProblema *problemF(tProblema *No);
tProblema *createDP(tProblema *No);
int checkPares(tProblema *No);
tProblema *addCaminhoGeral(tProblema *No);
tProblema *solveProblemF(tProblema *No, int linhaP, int colunaP, int *numPassosAux, int *maiorNumPassos, int *maiorCaminho);
