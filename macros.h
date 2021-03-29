#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sProblema
{
	int numProblema;
	int linhas;
	int colunas;
	char problema;
	int linha0;
	int linha0Aux;
	int coluna0;
	int coluna0Aux;
	int numPassos;
	int prob;
	int **matriz;
	int **visited;
	int **maiorCaminhoGeral;
	int **dp;
	int resposta;
	int respostaAux;
	int alocaV;
	int alocaM;
	struct sProblema *next;
}tProblema;
