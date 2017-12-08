#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
} No;

#define max(x,y) (((x)>(y)) ? (x) : (y))
#define MAXWORD 256

No *addtree(No *, char *);
void treeprint(No *);
int getword(char **);
char *mystrdup(char *s);

int main()
{
	No *root;
	char *word;

	root = NULL;
	while (getword(&word) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
	
	return 0;
}

No *addtree(No *root, char *word)
{
	int cond=0;
	No *p;

	p = root;

	if (p == NULL) {
		p = (No *) malloc(sizeof(No));
		p->word = strdup(word);
		p->count = 1;
		p->left = NULL;
		p->right = NULL;
	} else if ((cond = strcasecmp(word, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, word);
	else
		p->right = addtree(p->right, word);
	
	return p;
}

void treeprint(No *node)
{
	if (node == NULL) return;
	treeprint(node->left);
	printf("%s\n", node->word);
	treeprint(node->right);
}

int getword(char **w)
{
	int i=0;
	char c;
	char temp[MAXWORD];

	while ((c =  getchar()) != ' ' && c != '\n' && c != EOF)
		temp[i++] = c;
	
	if (c == EOF) return EOF;

	temp[i--] = '\0';
	*w = strdup(temp);

	return max(i,0);
}

char *mystrdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}
