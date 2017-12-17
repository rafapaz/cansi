#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 256
#define MAXFILENAME 32

typedef struct pos
{
	struct pos *prox;
	int value;
} posNo;

posNo *addPos(posNo *pos, int v);
void printTable(posNo **table);
void saveTable(FILE * fp, posNo **table);

int main(int argc, char **argv)
{
	int i=0, pos=0;
	char c, newName[MAXFILENAME];
	FILE *fpOrign = NULL;
	FILE *fpDest = NULL;
	posNo *table[256];

	for (i=0;i < MAXFILENAME;i++)
		newName[i] = '\0';

	for (i=0;i < MAXCHAR;i++)
		table[i] = NULL;

	fpOrign = fopen(argv[2], "r");
	fpDest = fopen(strcat(strcat(newName, argv[2]),".zap"), "w");

	while ((c = getc(fpOrign)) != EOF) {
		table[c] = addPos(table[c], pos++);
	}

	//printTable(table);
	saveTable(fpDest, table);

	fclose(fpOrign);
	fclose(fpDest);

	return 0;
}

void saveTable(FILE *fp, posNo **table)
{
	int i=0;
	posNo *p;

	for (i=0;i < MAXCHAR;i++) {
		if (table[i]==NULL) continue;

		fprintf(fp, "%c:", i);
		for (p = table[i]; p != NULL; p = p->prox)
			fprintf(fp, "%d,", p->value);
		fprintf(fp, "\n");
	}
}

void printTable(posNo **table)
{
	int i=0;
	posNo *p;

	for (i=0;i < MAXCHAR;i++) {
		printf("%c -> ", i);
		for (p = table[i]; p != NULL; p = p->prox)
			printf("%d -> ", p->value);
		printf("NULL\n");
	}
}

posNo *addPos(posNo *pos, int v)
{
	posNo *temp, *p;

	p = pos;

	temp = (posNo *) malloc(sizeof(posNo));
	temp->value = v;
	temp->prox = p;
	p = temp;

	return p;
}
