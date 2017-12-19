#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXCHAR 256
#define MAXFILENAME 32

typedef struct node
{
	char token;
	int freq;
	struct node *left, *right;
} Node;

Node *addNode(Node *root, char t, int f, int pos);
int comp(const void *v1, const void *v2);

int main(int argc, char **argv)
{
	int i=0, j=0, freqTemp[MAXCHAR], totalToken=0;
	char c, newName[MAXFILENAME];
	FILE *fpOrign = NULL;
	FILE *fpDest = NULL;
	
	Node *queue;

	for (i=0;i < MAXFILENAME;i++)
		newName[i] = '\0';
	for (i=0;i < MAXCHAR;i++)
		freqTemp[i] = 0;

	fpOrign = fopen(argv[2], "r");
	fpDest = fopen(strcat(strcat(newName, argv[2]),".zap"), "w");

	while ((c = getc(fpOrign)) != EOF) {
		freqTemp[c]++;
		totalToken++;
	}

	queue = NULL;

	for (i=0;i < MAXCHAR;i++) {
		if (freqTemp[i]) {
			addQueue(queue, i, freqTemp[i], totalToken);
		}
	}

	//qsort(freqTemp, MAXCHAR, sizeof(int), comp);
	//printf("%c:%d\n", i, freqTemp[i]);
	fclose(fpOrign);
	fclose(fpDest);

	return 0;
}

Node *addQueue(Node *q, char t, int f)
{
	Node *p;

	p = q;

	if (p == NULL) {
		p = (Node *) malloc(sizeof(Node));
		p->token = t;
		p->freq = f;
		
	}
}

Node *addNode(Node *root, char t, int f, int pos)
{
	Node *temp, *p;

	p = root;

	if (p == NULL) {
		p = (Node *) malloc(sizeof(Node));
		p->token = t;
		p->freq = f;
		p->left = temp->right = NULL;
	} else if (!pos)
		p->left = addNode(p->left, t, f, pos);
	else
		p->right = addNode(p->right, t, f, pos);
	
	return p;
}

int comp(const void *v1, const void *v2)
{
	return (*(int*)v1 - *(int*)v2);
}
