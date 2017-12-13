#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

typedef struct tnode {
	char *word;
	int count;
	int lines[MAXLINE];
	struct tnode *left;
	struct tnode *right;
} No;


No *addtree(No *, char *, int);
void treeprint(No *);

int main()
{
	No *root;
	char *word;
	int line=0;

	root = NULL;
	while (getword(&word, &line) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word, line);
	treeprint(root);
	
	return 0;
}

No *addtree(No *root, char *word, int line)
{
	int cond=0, j=0;
	No *p;

	p = root;

	if (p == NULL) {
		p = (No *) malloc(sizeof(No));
		p->word = strdup(word);
		p->count = 1;
		p->lines[0] = line;
		p->lines[1] = 0;
		p->left = NULL;
		p->right = NULL;
	} else if ((cond = strcmp(word, p->word)) == 0) {
		p->count++;
		for (j=0;p->lines[j];j++) {
			if (line == p->lines[j]) break;
		}
		p->lines[j] = line;
		p->lines[j+1] = 0;
	} else if (cond < 0)
		p->left = addtree(p->left, word, line);
	else
		p->right = addtree(p->right, word, line);
	
	return p;
}

void treeprint(No *node)
{
	int j;
	if (node == NULL) return;
	treeprint(node->left);
	printf("%s: ", node->word);
	for (j=0;node->lines[j];j++) 
		printf("%d ", node->lines[j]);
	printf("\n");

	treeprint(node->right);
}
