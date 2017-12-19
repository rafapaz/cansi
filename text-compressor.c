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
	int i=0, j=0, freqTemp[MAXCHAR], totalChar=0, alphaSize=0, min=0;
	char c, newName[MAXFILENAME];
	FILE *fpOrign = NULL;
	FILE *fpDest = NULL;
	Node queue[MAXCHAR];

	for (i=0;i < MAXFILENAME;i++)
		newName[i] = '\0';
	for (i=0;i < MAXCHAR;i++) {
		freqTemp[i] = 0;		
		queue[i].token = '\0';
		queue[i].freq = 0;
		queue[i].left = queue[i].right = NULL;
	}

	fpOrign = fopen(argv[2], "r");
	fpDest = fopen(strcat(strcat(newName, argv[2]),".zap"), "w");

	while ((c = getc(fpOrign)) != EOF) {
		freqTemp[c]++;
		totalChar++;
	}

	for (i=0;i < MAXCHAR;i++) {
		if (freqTemp[i]) {
			alphaSize++;
			pushSort(queue, i, freqTemp[i]);
		}
	}

	//qsort(freqTemp, MAXCHAR, sizeof(int), comp);
	//printf("%c:%d\n", i, freqTemp[i]);
	fclose(fpOrign);
	fclose(fpDest);

	return 0;
}

void pushSort(Node *q, char t, int f)
{
	int i, size_q=0;

	for (i=0;i<MAXCHAR;i++)
		if (q[i].freq) size_q++; 
	
	for (i=0;i < size_q; i++) {
		if (f <= q[i].freq) {
			for (j=size_q;j >= i;j--) {
				q[j+1].freq = q[j].freq;
			}
			break;
		}
	}
	q[i].token = t;
	q[i].freq = f;
}

Node popQueue(Node *q)
{
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
