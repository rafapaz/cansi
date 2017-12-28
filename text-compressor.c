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
	unsigned int totalChar=0;
	int i=0, j=0, freqTemp[MAXCHAR], maxCode=0, maxBits=0;
	int fdIn, fdOut, bytes_read, blockSizeBits, buffInt=0;
	FILE *fpIn = NULL;
	char c, tempFileName[MAXFILENAME], *newFile, *p, bufr[MAXCHAR];
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
	memset(tempFileName, '\0', MAXFILENAME);
	que.size = 0;
	for (i=0;i < MAXCHAR;i++) {
		freqTemp[i] = 0;		
		que.arr[i] = NULL;
		codeTable[i] = -1;
	}

	// Opening file
	fpIn = fopen(argv[2], "r");

	// Get frequencies
	while ((c = getc(fpIn)) != EOF) {
		if (c < 1 || c > 255) continue;
		freqTemp[c]++;
		totalChar++;
	}

	// Building a sorted queue
	for (i=0,j=0;i < MAXCHAR;i++) {
		if (freqTemp[i]) {
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

	printf("\nBefore\n\n");
	printf("maxBits: %d\n", maxBits);
	for (i=0;i < MAXCHAR;i++)
		if (codeTable[i] != (unsigned short)-1) printf("table[ %c ] = %d\n", i, codeTable[i]);

	fclose(fpIn);

	// Writing compressed file
	if (!(fdIn = open(argv[2], O_RDONLY, 0))) fail("Can open reader file");
	newFile = strcat(strcat(tempFileName, argv[2]),".zap");
	fdOut = open(newFile, O_WRONLY, 0766);

	blockSizeBits = 8 * sizeof(char) * maxBits;
	
	// Writing header
	write(fdOut, &maxBits, sizeof(int));
	for (i=0;i < MAXCHAR;i++) 
		write(fdOut, &(codeTable[i]), sizeof(unsigned short));


	// Writing text
	memset(bufr, '\0', MAXCHAR);
	buffInt = 0;
	while ((bytes_read = read(fdIn, bufr, blockSizeBits)) > 0) {
		for (p = bufr, i=1; *p != '\0'; p++, i++) {
			buffInt = buffInt | codeTable[*p];
			buffInt = buffInt << (blockSizeBits - (maxBits * i));
		}

		write(fdOut, &buffInt, blockSizeBits/8);
		buffInt = 0;
		memset(bufr, '\0', MAXCHAR);
	}
	

	close(fdIn);
	close(fdOut);

	printf("\nAfter\n\n");
	testDecompress(newFile);

	return 0;
}

void testDecompress(char *f)
{
	int fd, maxBits, i, reading;
	unsigned short table[MAXCHAR];
	char tableInv[MAXCHAR];

	fd = open(f, O_RDONLY, 0);
	read(fd, &maxBits, sizeof(int));
	printf("maxBits: %d\n", maxBits);

	for (i=0;i < MAXCHAR;i++) {
		read(fd, &table[i], sizeof(unsigned short));
		//if (table[i]!= (unsigned short)-1) tableInv[table[i]] = i;
	}

	for (i=0;i < MAXCHAR;i++) 
		if (table[i]!= (unsigned short)-1) printf("table[ %c ] = %d\n", i, table[i]);

	//while (reading = read(fd, &buf, maxBits)) {
		// TODO: bitwise operations 
		//printf("%c", );
	//}
	
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

void fail(char *)
{
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
