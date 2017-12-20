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
	Node *arr[MAXCHAR];
} Queue;

Node *addTree(Node *root, char t, int f, int pos);
Node *buildTree(Queue *q);
void pushSortedQueue(Queue *q, Node *n);
Node *popQueue(Queue * q);

int main(int argc, char **argv)
{
	int i=0, j=0, freqTemp[MAXCHAR], totalChar=0, alphaSize=0;
	char c, newName[MAXFILENAME];
	FILE *fpOrign = NULL;
	FILE *fpDest = NULL;
	Queue que;
	Node *rootTree, *temp;

	for (i=0;i < MAXFILENAME;i++)
		newName[i] = '\0';

	que.size = 0;
	for (i=0;i < MAXCHAR;i++) {
		freqTemp[i] = 0;		
		que.arr[i] = NULL;
	}

	fpOrign = fopen(argv[2], "r");
	fpDest = fopen(strcat(strcat(newName, argv[2]),".zap"), "w");

	// Get frequencies
	while ((c = getc(fpOrign)) != EOF) {
		freqTemp[c]++;
		totalChar++;
	}

	// Build a sorted queue
	for (i=0,j=0;i < MAXCHAR;i++) {
		if (freqTemp[i]) {
			alphaSize++;
			temp = (Node *) malloc(sizeof(Node));
			temp->token = i;
			temp->freq = freqTemp[i];
			temp->left = temp->right = NULL;			
			pushSortedQueue(&que, temp);
			j++;
		}
	}

	for (i=0;i<que.size;i++)
		printf("%c:%d\n", que.arr[i]->token, que.arr[i]->freq);

	printf("\n");
	// Build the tree
	rootTree = buildTree(&que);
	for (i=0;i<que.size;i++)
		printf("%c:%d -> left:%c:%d -> right:%c:%d\n", que.arr[i]->token, que.arr[i]->freq,
			que.arr[i]->left->token, que.arr[i]->left->freq, que.arr[i]->right->token, que.arr[i]->right->freq);

	fclose(fpOrign);
	fclose(fpDest);

	return 0;
}

Node *buildTree(Queue *q)
{
	Node *p, *node1, *node2;

	if (q->size > 1) {
		node1 = popQueue(q);
		node2 = popQueue(q);

		p = (Node *) malloc(sizeof(Node));
		p->token = '\0';
		p->freq = node1->freq + node2->freq;
		p->left = node2;
		p->right = node1;
		buildTree(q);
	} else if (q->size == 1)
		p = popQueue(q);

	pushSortedQueue(q, p);
	return p;
}

void pushSortedQueue(Queue *q, Node *n)
{
	int i,j;
	
	for (i=0;i < q->size; i++) {
		if (n->freq <= q->arr[i]->freq) {
			for (j=q->size;j >= i;j--) {
				q->arr[j+1] = q->arr[j];
			}
			break;
		}
	}
	q->arr[i] = n;
	q->size++;
}

Node *popQueue(Queue *q)
{
	int i;
	Node *ret;
	
	ret = q->arr[0];
	for (i=0;q->arr[i]!=NULL;i++)
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

