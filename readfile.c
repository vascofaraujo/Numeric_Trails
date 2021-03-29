#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "readfile.h"

extern tProblema *headP;

void openFile(FILE **fp, char *argv[]) 
{
	if(strstr(argv[1], ".puz") == NULL)		/* se o argumento passado na linha do terminal tem a extensão correta*/ 
		exit(0);

	*fp = fopen(argv[1], "r"); 

	if(*fp == NULL)
		exit(0);
}

void openFileOut(FILE **fs, char *argv[])
{
	int len =0, i, num_car = 0;
	len = strlen(argv[1]);
	char *nome_ficheiro = NULL, *aux = NULL, *aux_ficheiro = NULL;;


	aux = malloc((len+1) * sizeof(char));	
	aux_ficheiro = malloc((len+1) * sizeof(char));
	nome_ficheiro = malloc((len+2) * sizeof(char));
	
	aux[0] = '\0';
	aux_ficheiro[0] = '\0';
	nome_ficheiro[0] = '\0';

	strcpy(aux, argv[1]);

	for(i=0; i<=len; i++)				/* no caso de o nome do ficheiro ter mais que um ponto final*/
	{
		if(aux[i] == '.')
			num_car = num_car + 1;
	}

	for(i = 0; i < num_car; i++)		/* para ler tudo ate ao ultimo .puz */
	{
		if(i == 0)
			aux_ficheiro = strtok(argv[1], ".");
		if( i >= 1)
			aux_ficheiro = strtok(NULL, ".");
		strcat(nome_ficheiro, aux_ficheiro);
		strcat(nome_ficheiro, ".");
		strcpy(aux_ficheiro, "");

	}

	strcat(nome_ficheiro, "path");
	*fs = fopen(nome_ficheiro, "w"); 

	if(*fs == NULL)
		exit(0);
	free(aux);
	free(nome_ficheiro);
	//free(aux_ficheiro);
}

int testEntries(tProblema *novoP)		/* testa se as entradas estao corretas*/
{
	if( (strcmp(&novoP->problema, "A") !=0) && (strcmp(&novoP->problema, "B") != 0) && (strcmp(&novoP->problema, "C") != 0) && (strcmp(&novoP->problema, "D") != 0) && (strcmp(&novoP->problema, "E")!=0) && (strcmp(&novoP->problema, "F")!=0 ) )
		return 0;
	if( (novoP->linha0 >= novoP->linhas) || (novoP->linha0 < 0) ||(novoP->coluna0 >= novoP->colunas) || (novoP->coluna0 < 0) )
	{
		if(strcmp(&novoP->problema,"A") == 0 || strcmp(&novoP->problema, "B")==0)
		return 0;
	}
	if( ( strcmp(&novoP->problema, "A") == 0 || strcmp(&novoP->problema, "B")==0 || strcmp(&novoP->problema, "C")==0 || strcmp(&novoP->problema, "D")==0 )  && (novoP->numPassos < 1) )
		return 0;
	if( novoP->numPassos >= (novoP->linhas * novoP->colunas))
	{
		if(strcmp(&novoP->problema,"E") != 0 && strcmp(&novoP->problema, "F")!=0)
		{
			return 0;
		}
	}
	return 1;
}
 
void readFile(FILE **fp, int *numProblema)
{
	int linhasA, colunasA, linha0A, coluna0A, numPassosA;
	char tipoProblema[2] = {0};
	int valida = 0, valorMatriz = 0, moreProblems = 0;
	int i, j;
	

	tProblema *novoP = malloc(sizeof(tProblema));
	*numProblema = *numProblema+1;

	novoP= addNovoProblema(novoP, numProblema);
	novoP->prob = 0;
	if(fscanf(*fp, "%d %d %s %d %d %d", &linhasA, &colunasA, tipoProblema, &linha0A, &coluna0A, &numPassosA) == 6)
		novoP->prob = 1;  /* se novoP->prob = 0 e porque nao leu bem o ficheiro e nao deve fazerresolver problemas nem libertar memoria(ver main) */

	novoP = addGeral(novoP, linhasA, colunasA, tipoProblema, linha0A, coluna0A, numPassosA);

	valida = testEntries(novoP);

	if(valida == 0)
	{
		novoP->resposta = -1;
	}else novoP->resposta = 1;

	if(novoP->resposta != -1)
	{
		novoP->alocaM = 1;
		allocateMatrix(novoP, linhasA, colunasA);
	}else novoP->alocaM = 0;
	novoP->alocaV = 0;	

	for(i = 0; i < linhasA; i++)
	{
		for(j = 0; j < colunasA; j++)
		{
			fscanf(*fp, "%d", &valorMatriz);
			if(novoP->resposta != -1)
				novoP = addMatrix(novoP, valorMatriz, i, j);
		}
	}

}


void allocateMatrix(tProblema *novoP, int linhasA, int colunasA)
{
	int i;
	novoP->matriz = (int**) malloc(linhasA * sizeof(int*));

	if(novoP->matriz == NULL)
		exit(0);		

	for(i = 0; i < linhasA; i++)
	{
		novoP->matriz[i] = (int*) malloc(colunasA * sizeof(int));
		if(novoP->matriz[i] == NULL)
			exit(0);		
	}
}



void menu()
{
	if(headP->resposta != -1)
	{
		if(strcmp(&headP->problema, "A") == 0)
			headP = problemAB(headP);
		if(strcmp(&headP->problema, "B") == 0)
			headP = problemAB(headP);
		if(strcmp(&headP->problema, "C") == 0)
			headP = problemCD(headP);
		if(strcmp(&headP->problema, "D") == 0)
			headP = problemCD(headP);
		if(strcmp(&headP->problema, "E") == 0)
			headP = problemE(headP);
		if(strcmp(&headP->problema, "F") == 0)
			headP = problemF(headP);
	}

}

void printPath(FILE **fs)			/* funçao que vai escrevendo no ficheiro de saida a media que vai resolvendo cada problema */
{
	int i, auxLinha=0, auxColuna=0, numPassos = 0;
	if(headP->resposta != -1) 
	{
		fprintf(*fs, "%d %d %c %d %d %d %d ", headP->linhas, headP->colunas, headP->problema, headP->linha0, headP->coluna0, headP->numPassos, headP->resposta);
		if( (strcmp(&headP->problema, "E") == 0) || (strcmp(&headP->problema, "F") == 0) )
		{
			numPassos = headP->linhas * headP->colunas - 1;
			for(i = 0; i < numPassos; i++)
			{
				auxLinha = headP->maiorCaminhoGeral[i][0];
				auxColuna = headP->maiorCaminhoGeral[i][1];
				if(auxLinha != -1 && auxColuna != -1)
					fprintf(*fs, "\n%d %d %d", headP->maiorCaminhoGeral[i][0], headP->maiorCaminhoGeral[i][1], headP->matriz[auxLinha][auxColuna]);
			}
		}else{
			for(i = 0; i < headP->numPassos; i++)
			{
				auxLinha = headP->visited[i][0];
				auxColuna = headP->visited[i][1];
				if(auxLinha != -1 && auxColuna != -1)
					fprintf(*fs, "\n%d %d %d", headP->visited[i][0], headP->visited[i][1], headP->matriz[auxLinha][auxColuna]);
			}
		}
	}
	if(headP->resposta == -1)
		fprintf(*fs, "%d %d %c %d %d %d %d ", headP->linhas, headP->colunas, headP->problema, headP->linha0, headP->coluna0, headP->numPassos, headP->resposta);
	fprintf(*fs, "\n\n");


}


