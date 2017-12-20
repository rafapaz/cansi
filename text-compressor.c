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

typedef struct queue
{
	int size;
	Node arr[MAXCHAR];
} Queue;

Node *addTree(Node *root, char t, int f, int pos);
void pushSortedQueue(Queue *q, char t, int f);
Node popQueue(Queue * q);

int main(int argc, char **argv)
{
	int i=0, j=0, freqTemp[MAXCHAR], totalChar=0, alphaSize=0;
	char c, newName[MAXFILENAME];
	FILE *fpOrign = NULL;
	FILE *fpDest = NULL;
	Queue que;
	Node *rootTree, leaf;

	for (i=0;i < MAXFILENAME;i++)
		newName[i] = '\0';

	que.size = 0;
	for (i=0;i < MAXCHAR;i++) {
		freqTemp[i] = 0;		
		que.arr[i].token = '\0';
		que.arr[i].freq = 0;
		que.arr[i].left = que.arr[i].right = NULL;
	}

	fpOrign = fopen(argv[2], "r");
	fpDest = fopen(strcat(strcat(newName, argv[2]),".zap"), "w");

	// Get frequencies
	while ((c = getc(fpOrign)) != EOF) {
		freqTemp[c]++;
		totalChar++;
	}

	// Build a sorted queue
	for (i=0;i < MAXCHAR;i++) {
		if (freqTemp[i]) {
			alphaSize++;
			pushSortedQueue(&que, i, freqTemp[i]);
		}
	}

	// Build the tree
	while (que.size) {
		node1 = popQueue(&que);
		if (que.size > 1) node2 = popQueue(&que);
	}

	fclose(fpOrign);
	fclose(fpDest);

	return 0;
}

void pushSortedQueue(Queue *q, char t, int f)
{
	int i,j;
	
	for (i=0;i < q->size; i++) {
		if (f <= q->arr[i].freq) {
			for (j=q->size;j >= i;j--) {
				q->arr[j+1] = q->arr[j];
			}
			break;
		}
	}
	q->arr[i].token = t;
	q->arr[i].freq = f;
	q->size++;
}

Node popQueue(Queue *q)
{
	int i;
	Node ret;
	
	ret = q->arr[0];
	for (i=0;q->arr[i].freq;i++)
		q->arr[i] = q->arr[i+1];
	
	q->size = (q->size < 1) ? 0 : --(q->size);
	return ret;
}

Node *addTree(Node *root, char t, int f, int pos)
{
	Node *temp, *p;

	p = root;

	if (p == NULL) {
		p = (Node *) malloc(sizeof(Node));
		p->token = t;
		p->freq = f;
		p->left = temp->right = NULL;
	} else if (!pos)
		p->left = addTree(p->left, t, f, pos);
	else
		p->right = addTree(p->right, t, f, pos);
	
	return p;
}

