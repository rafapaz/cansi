#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define MAX 999
#define LEN 32

int comp(const void *n1, const void *n2);

int main()
{
	int line=0, i=0, size=0;
	char *w;
	char lista[MAX][LEN];

	while ((getword(&w, &line)) != EOF) {
		strcpy(lista[i], w);
		i++;
	}
	size = i;
	strcpy(lista[i],"\0");

	printf("\nNormal: \n");
	for (i=0;strcmp(lista[i],"\0");i++)
		printf("%s\n", lista[i]);

	qsort(lista, size, sizeof(char)*MAX*LEN, comp);

	printf("Ordenado: \n");
	for (i=0;strcmp(lista[i],"\0");i++)
		printf("%s\n", lista[i]);
	
	return 0;
}


int comp(const void *n1, const void *n2)
{
	return strcmp((char *)n1,(char *)n2);
}
