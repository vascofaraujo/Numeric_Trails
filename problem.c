#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <setjmp.h> 
#include "problem.h"

jmp_buf out;

tProblema *problemAB(tProblema *No)
{
	int linhaAux=0, colunaAux=0, numPassosAux = 0, auxMovimento = 0, i, j;
	linhaAux = No->linha0;
	colunaAux = No->coluna0;
	No = createVisited(No);
	if(No->resposta != -1)

	{
		if(!setjmp(out))
		{
			if(strcmp(&No->problema, "A") == 0)
				No = solveProblemAC(No, linhaAux, colunaAux, &numPassosAux);
			if(strcmp(&No->problema, "B") == 0)
				No = solveProblemBD(No, linhaAux, colunaAux, &numPassosAux);
		}
	}
	if(No->visited[No->numPassos-1][0] == -1 && No->visited[No->numPassos-1][1]== -1)		/*se nao encontrou um camino com o numero de passos pretendido */
		No->resposta = -1;
	return No;
}

tProblema *problemCD(tProblema *No)
{
	int i, j, exit = 0;
	int linhaAux=0, colunaAux=0, numPassosAux = 0;
		
	No = createVisited(No);

	for(i = 0 ; i < No->linhas && exit == 0 ; i++)
	{
		for( j = 0; j < No->colunas && exit == 0; j++)
		{       
			numPassosAux = 0;
			linhaAux = i;
			colunaAux = j;
			No->linha0 = linhaAux;
			No->coluna0 = colunaAux;
			
			if(!setjmp(out))
			{
				if(strcmp(&No->problema, "C") == 0)
				{
					No = solveProblemAC(No, linhaAux, colunaAux, &numPassosAux);
				}
				if(strcmp(&No->problema, "D") == 0)
					No = solveProblemBD(No, linhaAux, colunaAux, &numPassosAux);
			}
			if(No->visited[No->numPassos-1][0] == -1 && No->visited[No->numPassos-1][1]== -1)
					No->resposta = -1;

			if(No->resposta != -1)
				exit = 1;
		}
	}
	if(No->resposta == -1)
	{
		No->linha0 = No->linha0Aux;
		No->coluna0 = No->coluna0Aux;
	}
	return No;
}
	

tProblema *createVisited(tProblema *No)
{
	int i, colunas = 2;
	No->alocaV = 1;
	No->visited = (int**)malloc((No->numPassos) * sizeof(int*));
	if(No->visited == NULL)
		exit(0);		

	for(i = 0; i < No->numPassos; i++)
	{
		No->visited[i] = (int*) malloc(colunas * sizeof(int));
		if(No->visited[i] == NULL)
			exit(0);
	}
	for(i = 0; i < No->numPassos; i++)
	{
		No->visited[i][0] = -1;
		No->visited[i][1] = -1;
	}
	return No;
}


tProblema *solveProblemAC(tProblema *No, int linhaP, int colunaP, int *numPassosAux)
{
	int linhaI, colunaI, linhaF, colunaF, i, j;
	linhaI = linhaP-1;
	colunaI = colunaP-1;
	linhaF = linhaP+1;
	colunaF = colunaP+1;
	if(*numPassosAux == No->numPassos)
	{
		No->resposta = No->numPassos;
		longjmp(out, 1); 		/* salta para a funçao de que foi chamada (ProblemAB ou ProblemaCD) */
	}
	if((*numPassosAux != No->numPassos))
	{
		if(linhaP-1 <= 0)
			linhaI = 0;
		if(colunaP-1 <= 0)
			colunaI = 0;
		if(linhaP+1 >= No->linhas)
			linhaF = linhaP;
		if(colunaP+1 >= No->colunas)
			colunaF = colunaP;
		for(i = linhaI; i <= linhaF ; i++)
		{
			for(j = colunaI; j <= colunaF ; j++)
			{	
				if(No->matriz[i][j] > No->matriz[linhaP][colunaP])
				{
					if(visited(No, *numPassosAux, i, j) == 0)		/* se o caminho nao tiver ja passado por esse ponto*/
					{
						No->visited[*numPassosAux][0] = i;
						No->visited[*numPassosAux][1] = j;
						*numPassosAux = *numPassosAux + 1;
						solveProblemAC(No, i, j, numPassosAux);
					}
					
				}
			}
		}
	}
	*numPassosAux = *numPassosAux - 1; 	/* diminui o numero de passos para fazer o backtracking */
	if(*numPassosAux == -1)
		longjmp(out, 1);
	for(i = *numPassosAux; i < No->numPassos; i++) 	/*limpa a matriz visited */
	{
		No->visited[i][0] = -1;
		No->visited[i][1] = -1;
	}
}

int visited(tProblema *No, int numPassos, int linha, int coluna)
{
	int i;
	for(i = 0; i < numPassos; i++)
	{
		if(linha == No->visited[i][0] && coluna == No->visited[i][1])
			return 1;		/* se ja passou nesse ponto */
	}
	return 0;
}
tProblema *solveProblemBD(tProblema *No, int linhaP, int colunaP, int *numPassosAux)
{
	int linhaI, colunaI, linhaF, colunaF, i, j;
	linhaI = linhaP-1;
	colunaI = colunaP-1;
	linhaF = linhaP+1;
	colunaF = colunaP+1;
	if(*numPassosAux == No->numPassos)
	{
		No->resposta = No->numPassos;
		longjmp(out, 1);
	}
	if((*numPassosAux != No->numPassos))
	{

		if(linhaP-1 <= 0)
			linhaI = 0;
		if(colunaP-1 <= 0)
			colunaI = 0;
		if(linhaP+1 >= No->linhas)
			linhaF = linhaP;
		if(colunaP+1 >= No->colunas)
			colunaF = colunaP;
		for(i = linhaI; i <= linhaF ; i++)
		{
			for(j = colunaI; j <= colunaF ; j++)
			{	
				if(No->matriz[i][j] % 2 == 0) 
				{
					if( (visited(No, *numPassosAux, i, j) == 0) && ((i!=No->linha0) || (j!=No->coluna0)))
					{
						No->visited[*numPassosAux][0] = i;
						No->visited[*numPassosAux][1] = j;
						*numPassosAux = *numPassosAux + 1;
						solveProblemBD(No, i, j, numPassosAux);
					}
					
				}
			}
		}
	}
	*numPassosAux = *numPassosAux - 1; 
	if(*numPassosAux == -1)
		longjmp(out, 1);
	for(i = *numPassosAux; i < No->numPassos; i++)
	{
		No->visited[i][0] = -1;
		No->visited[i][1] = -1;
	}
}


tProblema *problemE(tProblema *No)
{
	int i, j, z, exit = 0;
	int linhaAux=0, colunaAux=0, numPassosAux = 0, maiorNumPassos = 0, maiorCaminho = 0, maxNumPassos;
	maxNumPassos = No->linhas * No->colunas - 1;
		
	No = createVisitedE(No);
	No = createBiggestGlobalPath(No);
	No = createDP(No);
	for(i = 0 ; i < No->linhas; i++)
	{
		for( j = 0; j < No->colunas; j++)
		{  
			maiorNumPassos = 0;
			numPassosAux = 0;
			linhaAux = i;
			colunaAux = j;
			No->linha0Aux = linhaAux;
			No->coluna0Aux = colunaAux;
			if(!setjmp(out))
			{
				if(No->dp[i][j] == -1)
					No = solveProblemE(No, linhaAux, colunaAux, &numPassosAux, &maiorNumPassos, &maiorCaminho);
			}
			if(maiorCaminho == maxNumPassos)
			{
				i = No->linhas;
				j = No->colunas;
			}
		}
	}
	if(maiorCaminho == 0)
		No->resposta = -1;
	return No;
}


tProblema *createVisitedE(tProblema *No)
{
	int i, colunas = 2, maxNumPassos;
	No->alocaV = 1;
	maxNumPassos = No->linhas * No->colunas -1;
	No->visited = (int**)malloc((maxNumPassos) * sizeof(int*));
	if(No->visited == NULL)
		exit(0);		

	for(i = 0; i < maxNumPassos; i++)
	{
		No->visited[i] = (int*) malloc(colunas * sizeof(int));
		if(No->visited[i] == NULL)
			exit(0);		
	}
	for(i = 0; i < maxNumPassos; i++)
	{
		No->visited[i][0] = -1;
		No->visited[i][1] = -1;
	}
	return No;
}

tProblema *createBiggestGlobalPath(tProblema *No)
{
	int i, colunas = 2, maxNumPassos;
	No->alocaV = 1;
	maxNumPassos = No->linhas * No->colunas -1;
	No->maiorCaminhoGeral = (int**)malloc((maxNumPassos) * sizeof(int*));
	if(No->maiorCaminhoGeral == NULL)
		exit(0);		

	for(i = 0; i < maxNumPassos; i++)
	{
		No->maiorCaminhoGeral[i] = (int*) malloc(colunas * sizeof(int));
		if(No->maiorCaminhoGeral[i] == NULL)
			exit(0);		
	}
	for(i = 0; i < maxNumPassos; i++)
	{
		No->maiorCaminhoGeral[i][0] = -1;
		No->maiorCaminhoGeral[i][1] = -1;
	}
	return No;
}



tProblema *solveProblemE(tProblema *No, int linhaP, int colunaP, int *numPassosAux, int *maiorNumPassos, int *maiorCaminho)
{
	int linhaI, colunaI, linhaF, colunaF, i, j, flag = 0, maxNumPassos;
	linhaI = linhaP-1;
	colunaI = colunaP-1;
	linhaF = linhaP+1;
	colunaF = colunaP+1;
	maxNumPassos = No->linhas * No->colunas - 1;
	
	if(*maiorNumPassos > 0 && linhaP == No->linha0Aux && colunaP == No->coluna0Aux)
	{
		No->resposta = *maiorNumPassos;
		longjmp(out, 1);
	}
	if(*numPassosAux == maxNumPassos)
	{
		No->resposta = *numPassosAux;
		longjmp(out, 1);
	}

	if(linhaP-1 <= 0)
		linhaI = 0;
	if(colunaP-1 <= 0)
		colunaI = 0;
	if(linhaP+1 >= No->linhas)
		linhaF = linhaP;
	if(colunaP+1 >= No->colunas)
		colunaF = colunaP;
	for(i = linhaI; i <= linhaF ; i++)
	{
		for(j = colunaI; j <= colunaF ; j++)
		{
			if(No->matriz[i][j] > No->matriz[linhaP][colunaP])
			{	
				if(visited(No, *numPassosAux, i, j) == 0)
				{	
					flag = 1;
					No->visited[*numPassosAux][0] = i;
					No->visited[*numPassosAux][1] = j;
					*numPassosAux = *numPassosAux + 1;
					solveProblemE(No, i, j, numPassosAux, maiorNumPassos, maiorCaminho);
				}
			}
		}
	}
	if(flag == 0)
	{
		if(*numPassosAux > *maiorNumPassos)
		{
			*maiorNumPassos = *numPassosAux;
			if(*maiorNumPassos > *maiorCaminho) 	/* compara com o maior caminho ate a data */
			{
				*maiorCaminho = *maiorNumPassos;
				No->resposta = *maiorCaminho;
				No->linha0 = No->linha0Aux;
				No->coluna0 = No->coluna0Aux;
				for(i = 0; i < *maiorNumPassos; i++)
				{
					No->maiorCaminhoGeral[i][0] = No->visited[i][0];
					No->maiorCaminhoGeral[i][1] = No->visited[i][1];
				}
			}
		}
	}
	*numPassosAux = *numPassosAux - 1; 
	if(*numPassosAux == -1)
		longjmp(out, 1);
	for(i = *numPassosAux; i < maxNumPassos; i++)
	{
		No->visited[i][0] = -1;
		No->visited[i][1] = -1;
	}
	No->dp[linhaP][colunaP] = 1;
}


tProblema *problemF(tProblema *No)
{
	int i, j, z, exit = 0;
	int linhaAux=0, colunaAux=0, numPassosAux = 0, maiorNumPassos = 0, maiorCaminho = 0, maxNumPassos, tudoPar = 0;
	maxNumPassos = No->linhas * No->colunas - 1;
	
	No = createVisitedE(No);
	No = createBiggestGlobalPath(No);
	No = createDP(No);
	for(i = 0 ; i < No->linhas; i++)
	{
		for( j = 0; j < No->colunas; j++)
		{  
			maiorNumPassos = 0;
			numPassosAux = 0;
			linhaAux = i;
			colunaAux = j;
			No->linha0Aux = linhaAux;
			No->coluna0Aux = colunaAux;
			tudoPar = checkPares(No);		/* verifica se a matriz nao e toda par para nao ter que encontrar o caminho atraves do DFS para poupar tempo */
			if(tudoPar == maxNumPassos+1)
			{
				maiorCaminho = maxNumPassos;
				No->resposta = maxNumPassos;
				No->linha0 = 0;
				No->coluna0 = 0;
				No = addCaminhoGeral(No);
			}else{
				if(!setjmp(out))
				{
					if(No->dp[i][j] == -1)
						No = solveProblemF(No, linhaAux, colunaAux, &numPassosAux, &maiorNumPassos, &maiorCaminho);
				}
			}
			if(maiorCaminho == maxNumPassos)
			{
				i = No->linhas;
				j = No->colunas;
			}
		}
	}
	if(maiorCaminho == 0)
		No->resposta = -1;
	return No;
}

tProblema *createDP(tProblema *No)
{
	int i, j;
	No->dp = (int**)malloc((No->linhas) * sizeof(int*));
	if(No->dp == NULL)
		exit(0);		

	for(i = 0; i < No->linhas; i++)
	{
		No->dp[i] = (int*) malloc(No->colunas * sizeof(int));
		if(No->dp[i] == NULL)
			exit(0);		
	}
	for(i = 0; i < No->linhas; i++)
	{
		for(j = 0; j < No->colunas; j++)
			No->dp[i][j] = -1;
	}
	return No;
}


int checkPares(tProblema *No)
{
	int i, j, pares = 0;
	for(i = 0; i < No->linhas; i++)
	{
		for(j = 0; j < No->colunas; j++)
		{
			if(No->matriz[i][j] % 2 == 0)
				pares++; 		/* numero de pares namatriz */
		}
	}
	return pares;
}

tProblema *addCaminhoGeral(tProblema *No)
{
	int i, j, z=0;

	for(i = 0; i < No->linhas ; i++)
	{
		if(i % 2 == 0)
		{
			for(j = 1; j < No->colunas ; j++)
			{
				No->maiorCaminhoGeral[z][0] = i;
				No->maiorCaminhoGeral[z][1] = j;
				z++;
			}
		}else{
			for(j = No->colunas-1; j >= 0; j--)
			{
				No->maiorCaminhoGeral[z][0] = i;
				No->maiorCaminhoGeral[z][1] = j;
				z++;
			}
		}
	}
	return No;
}

tProblema *solveProblemF(tProblema *No, int linhaP, int colunaP, int *numPassosAux, int *maiorNumPassos, int *maiorCaminho)
{
	int linhaI, colunaI, linhaF, colunaF, i, j, flag = 0, maxNumPassos;
	linhaI = linhaP-1;
	colunaI = colunaP-1;
	linhaF = linhaP+1;
	colunaF = colunaP+1;
	maxNumPassos = No->linhas * No->colunas - 1;
	
	if(*maiorNumPassos > 0 && linhaP == No->linha0Aux && colunaP == No->coluna0Aux)
	{
		No->resposta = *maiorNumPassos;
		longjmp(out, 1);
	}
	if(*numPassosAux == maxNumPassos)
	{
		No->resposta = *numPassosAux;
		longjmp(out, 1);
	}

	if(linhaP-1 <= 0)
		linhaI = 0;
	if(colunaP-1 <= 0)
		colunaI = 0;
	if(linhaP+1 >= No->linhas)
		linhaF = linhaP;
	if(colunaP+1 >= No->colunas)
		colunaF = colunaP;
	for(i = linhaI; i <= linhaF ; i++)
	{
		for(j = colunaI; j <= colunaF ; j++)
		{	
			if(No->matriz[i][j] % 2 == 0)
			{	
				if(visited(No, *numPassosAux, i, j) == 0 && (i != No->linha0Aux || j != No->coluna0Aux))
				{	
					flag = 1;
					No->visited[*numPassosAux][0] = i;
					No->visited[*numPassosAux][1] = j;
					*numPassosAux = *numPassosAux + 1;
					solveProblemF(No, i, j, numPassosAux, maiorNumPassos, maiorCaminho);
				}
			}
		}
	}
	if(flag == 0)
	{
		if(*numPassosAux > *maiorNumPassos)
		{
			*maiorNumPassos = *numPassosAux;
			if(*maiorNumPassos > *maiorCaminho)
			{
				*maiorCaminho = *maiorNumPassos;
				No->resposta = *maiorCaminho;
				No->linha0 = No->linha0Aux;
				No->coluna0 = No->coluna0Aux;
				for(i = 0; i < *maiorNumPassos; i++)
				{
					No->maiorCaminhoGeral[i][0] = No->visited[i][0];
					No->maiorCaminhoGeral[i][1] = No->visited[i][1];
				}
			}
		}
	}
	*numPassosAux = *numPassosAux - 1; 
	if(*numPassosAux == -1)
		longjmp(out, 1);
	for(i = *numPassosAux; i < maxNumPassos; i++)
	{
		No->visited[i][0] = -1;
		No->visited[i][1] = -1;
	}
	No->dp[linhaP][colunaP] = 1;
}

