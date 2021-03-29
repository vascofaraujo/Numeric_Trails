#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"

tProblema *headP;

int main(int argc, char *argv[])
{
	FILE *fp, *fs;
	int numProblema = 0;
	openFile(&fp, argv);
	openFileOut(&fs, argv);

	while(!feof(fp))
	{
		headP = NULL;
		readFile(&fp, &numProblema); 
		if(headP->prob == 1)
		{
			menu();
			printPath(&fs);
			freeMemory(&fp);
		}
	}
	free(headP);
	fclose(fp);
	fclose(fs);
	return 0;
}
