#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"

int getword(char **w, int *line)
{
	int i=0;
	char c;
	char temp[MAXWORD];
	static int l=1;

	while ((c =  getchar()) != ' ' && c != '\n' && c != EOF)
		temp[i++] = c;
	
	*line = l;
	l += (c == '\n');
	if (c == EOF) return EOF;

	temp[i--] = '\0';
	*w = strdup(temp);

	return max(i,0);
}

/* mygetline: read a line into s, return length */
int mygetline(char **s)
{
	int c, i;
	char temp[MAXLINE];

	for (i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
		temp[i] = c;
	}
	if (c == '\n') {
		temp[i] = c;
		++i;
	}

	temp[i] = '\0';
	*s = mystrdup(temp);
	return i;
}

char *mystrdup(char *s)
{
	char *p;

	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

