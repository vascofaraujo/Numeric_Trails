#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"

tProblema *addNovoProblema(tProblema *novoP, int *numProblema);
tProblema *addGeral(tProblema *novoP, int linhasA, int colunasA, char *tipoProblema, int linhas0A, int coluans0A, int numPassos);
tProblema *addMatrix(tProblema *novoP, int valor, int linha, int coluna);
void freeMemory();

