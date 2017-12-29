#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <inttypes.h>

#define MAXCHAR 256
#define MAXFILENAME 32
#define MAXBUF 64
#define min(a,b) (((a) < (b)) ? (a) : (b))

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
void pushQueue(Queue *q, Node *n);
Node *popQueue(Queue * q);
void walkTree(Node *n, unsigned short bit, unsigned short *table);
int sizeInBits(int number);
void testDecompress(char *f);
static void die(const char *fmt, ...);


int main(int argc, char **argv)
{
	uint64_t buffInt=0;
	unsigned int totalChar=0;
	int i=0, j=0, freqTemp[MAXCHAR], maxCode=0, maxBits=0;
	int fdIn, fdOut, bytes_read, blockSizeBits;
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
	newFile = strcat(strcat(tempFileName, argv[2]),".zap");
	if ((fdIn = open(argv[2], O_RDONLY, 0)) == -1) die("Cannot open reader file");
	if ((fdOut = open(newFile, O_WRONLY | O_CREAT, 0766)) == -1) die("Cannot open file to write");

	blockSizeBits = 8 * sizeof(char) * maxBits;
	
	// Writing header
	write(fdOut, &maxBits, sizeof(int));
	for (i=0;i < MAXCHAR;i++) 
		write(fdOut, &(codeTable[i]), sizeof(unsigned short));


	// Writing text
	memset(bufr, '\0', MAXCHAR);
	buffInt = 0;
	while ((bytes_read = read(fdIn, bufr, 8)) > 0) {
		for (p = bufr, i=1; *p != '\0'; p++, i++) {
			buffInt = buffInt | codeTable[*p];
			buffInt = buffInt << ((sizeof(uint64_t) * 8) - (maxBits * i));
		}

		write(fdOut, &buffInt, blockSizeBits/8);
		buffInt = 0;
		memset(bufr, '\0', MAXCHAR);
	}
	

	close(fdIn);
	close(fdOut);

	//printf("\nAfter\n\n");
	testDecompress(newFile);

	return 0;
}

void testDecompress(char *f)
{
	uint64_t buf, code, mask;
	int fdIn, fdOut, maxBits, i, reading;
	unsigned short table[MAXCHAR];
	char tableInv[MAXCHAR], tempFileName[MAXFILENAME], *newFile;

	memset(tempFileName, '\0', MAXFILENAME);
	newFile = strcat(strcat(tempFileName, f),".final");
	if ((fdIn = open(f, O_RDONLY, 0)) == -1)
		die("Decompressing: cannot open reader file");
	if ((fdOut = open(newFile, O_WRONLY | O_CREAT, 0766)) == -1)
		die("Decompressing: cannot open file to write");

	read(fdIn, &maxBits, sizeof(int));
	//printf("maxBits: %d\n", maxBits);

	for (i=0;i < MAXCHAR;i++) {
		read(fdIn, &table[i], sizeof(unsigned short));
		if (table[i]!= (unsigned short)-1) tableInv[table[i]] = i;
	}

	//for (i=0;i < MAXCHAR;i++) 
	//	if (table[i]!= (unsigned short)-1) printf("table[ %c ] = %d\n", i, table[i]);
	//for (i=0;i < MAXCHAR;i++)
	//	printf("tableInv[ %d ] = %c\n", i, tableInv[i]);

	buf = 0;
	while ((reading = read(fdIn, &buf, 8)) > 0) {
		// TODO: bitwise operations 
		for (i=1;i < (sizeof(uint64_t)*reading)/maxBits; i++) {
			code = buf >> ((sizeof(uint64_t) * 8) - (maxBits * i));
			mask = (((uint64_t)~0) >> (sizeof(uint64_t) - maxBits));
			code = code & mask;
			write(fdOut, &tableInv[(int)code], sizeof(char));
		}
		//putchar(tableInv[buf]);
		buf = 0;
	}
	
	close(fdIn);
	close(fdOut);
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
		p->left = node1;
		p->right = node2;
		buildOneLevelTree(q);
	} else if (q->size == 1)
		p = popQueue(q);

	if (p!=NULL) pushQueue(q, p);

	return p;
}

void pushQueue(Queue *q, Node *n)
{
	int i,j;
	
	q->arr[q->size] = n;
	q->size++;
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

static void die(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	fputc('\n', stderr);
	perror("SO says: ");
	exit(1);
}
