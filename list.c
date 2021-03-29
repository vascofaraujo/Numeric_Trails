#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

extern tProblema *headP;

tProblema *addNovoProblema(tProblema *novoP, int *numProblema)
{
	novoP->numProblema = *numProblema;
	novoP->next = NULL;

	if(headP == NULL)
		headP = novoP;	
	else exit(0);
		
	return novoP;
}


tProblema *addGeral(tProblema *novoP, int linhasA, int colunasA, char *tipoProblema, int linhas0A, int colunas0A, int numPassosA)
{
	novoP->linhas = linhasA;
	novoP->colunas = colunasA;
	strcpy(&(novoP->problema),tipoProblema);
	novoP->linha0 = linhas0A;
	novoP->linha0Aux = linhas0A;
	novoP->coluna0 = colunas0A;
	novoP->coluna0Aux = colunas0A;
	novoP->numPassos = numPassosA;
	return novoP;
}
	

tProblema *addMatrix(tProblema *novoP, int valor, int linha, int coluna)
{
	novoP->matriz[linha][coluna] = valor;
	return novoP;
}


void freeMemory()
{
	int i, numPassos = 0;
	if(headP->alocaM == 1) 	/*se alocou a matriz*/
	{
		for(i = 0; i < headP->linhas; i++)
			free(headP->matriz[i]);
		free(headP->matriz);
	}
	if(headP->alocaV == 1)
	{
		if(strcmp(&headP->problema, "E") == 0 || strcmp(&headP->problema, "F") == 0)	/* se o problema e E ou F e porque alocou o maiorCaminhoGeral*/
		{
			numPassos = headP->linhas * headP->colunas - 1;
			for(i = 0; i < numPassos; i++)
				free(headP->maiorCaminhoGeral[i]);
			free(headP->maiorCaminhoGeral);
			for(i = 0; i < headP->linhas; i++)
				free(headP->dp[i]);
			free(headP->dp);
		}else numPassos = headP->numPassos;
		for(i = 0; i < numPassos; i++)
			free(headP->visited[i]);
		free(headP->visited);
	}

}


