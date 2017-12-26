#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXCHAR 256
#define MAXFILENAME 32
#define MAXBUF 64

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
Node *buildTree(Queue *q, int totalFreq);
Node *buildOneLevelTree(Queue *q);
void pushSortedQueue(Queue *q, Node *n);
Node *popQueue(Queue * q);
void walkTree(Node *n, unsigned short bit, unsigned short *table);
int sizeInBits(int number);
void testDecompress(char *f);

int main(int argc, char **argv)
{
	int i=0, j=0, freqTemp[MAXCHAR], totalChar=0, alphaSize=0, maxCode=0, maxBits=0;
	int fdIn, fdOut, bytes_read, bufr[MAXCHAR], blockSizeBits, buffInt=0;
	FILE *fpIn = NULL;
	char c, tempFileName[MAXFILENAME], *newFile, *p;
	Queue que;
	Node *rootTree, *temp;
	unsigned short codeTable[MAXCHAR];

	if (argc < 3 && !(strcmp(argv[1],"-c") || strcmp(argv[1],"-d"))) {
		printf("Usage: zap -c|-d <filename>\n");
		printf("       -c : compress\n");
		printf("       -d : decompress\n");
		exit(1);
	}

	// Init everything
	//for (i=0;i < MAXFILENAME;i++)
	//	tempFileName[i] = '\0';
	memset(tempFileName, '\0', MAXFILENAME);

	que.size = 0;
	for (i=0;i < MAXCHAR;i++) {
		freqTemp[i] = 0;		
		que.arr[i] = NULL;
		codeTable[i] = -1;
	}
	
	// Opening files
	fpIn = fopen(argv[2], "r");

	// Get frequencies
	while ((c = getc(fpIn)) != EOF) {
		freqTemp[c]++;
		totalChar++;
	}

	// Building a sorted queue
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

	// Building the tree	
	rootTree = buildTree(&que, totalChar);
	walkTree(rootTree, 0, codeTable);

	// Getting max bit block
	for (i=0,j=0;i < MAXCHAR;i++) 
		if (codeTable[i] != (unsigned short)-1) 
			maxCode = (codeTable[i] > maxCode) ? codeTable[i] : maxCode;
			//printf("%c:%d\n", i, codeTable[i]);
	maxBits = sizeInBits(maxCode);

	fclose(fpIn);

	// Writing compressed file
	fdIn = open(argv[2], O_RDONLY, 0);
	newFile = strcat(strcat(tempFileName, argv[2]),".zap");
	fdOut = open(newFile, O_WRONLY, 0666);

	blockSizeBits = 8 * sizeof(char) * maxBits;
	
	// Writing header
	write(fdOut, &maxBits, sizeof(int));
	for (i=0;i < MAXCHAR;i++) 
		write(fdOut, &(codeTable[i]), sizeof(unsigned short));
	

	/*
	memset(bufr, '\0', MAXCHAR);
	buffInt = 0;
	while ((bytes_read = read(fdIn, bufr, blockSizeInBits)) > 0) {
		for (p = bufr, i=1; *p != '\0'; p++, i++) {
			buffInt = buffInt | *p;
			buffInt = buffInt << (blockSizeBits - (maxBits * i));
		}

		buffInt = 0;
		memset(bufr, '\0', MAXCHAR);
	}
	*/

	close(fdIn);
	close(fdOut);

	testDecompress(newFile);

	return 0;
}

void testDecompress(char *f)
{
	int fd, maxBits, i;
	unsigned short table[MAXCHAR];

	fd = open(f, O_RDONLY, 0);
	read(fd, &maxBits, sizeof(int));
	printf("maxBits: %d\n", maxBits);
	for (i=0;i < MAXCHAR;i++) 
		read(fd, &table[i], sizeof(unsigned short));
	for (i=0;i < MAXCHAR;i++) 
		if (table[i]!= (unsigned short)-1) printf("table[ %c ] = %d\n", i, table[i]);
	close(fd);
}

int sizeInBits(int number) 
{
	int r=1;

	while (number = (number >> 1))
		r++;
	
	return r;
}

void walkTree(Node *n, unsigned short bit, unsigned short *table)
{
	if (n==NULL)
		return;
	
	if (n->token != '\0')
		table[n->token] = bit;
		//addCodeTable(table, n->token, bit);

	walkTree(n->left, (bit << 1) | 0, table);
	walkTree(n->right, (bit << 1) | 1, table);
}

Node *buildTree(Queue *q, int totalFreq)
{
	Node *p, *node1, *node2;
	
	p = NULL;

	while (q->arr[0]->freq < totalFreq)
		p = buildOneLevelTree(q);

	return p;
}

Node *buildOneLevelTree(Queue *q)
{
	Node *p, *node1, *node2;
	
	p = NULL;

	if (q->size > 1) {
		node1 = popQueue(q);
		node2 = popQueue(q);

		p = (Node *) malloc(sizeof(Node));
		p->token = '\0';
		p->freq = node1->freq + node2->freq;
		p->left = node2;
		p->right = node1;
		buildOneLevelTree(q);
	} else if (q->size == 1)
		p = popQueue(q);

	if (p!=NULL) pushSortedQueue(q, p);

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

/*
void addCodeTable(Code *table, char token, unsigned short code)
{
	Code *p, *temp;

	temp = (Code *) malloc(sizeof(Code));
	temp->token = token;
	temp->code = code;

	p = table;
	temp->next = p->next;
	p->next = temp;
}
*/
