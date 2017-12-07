#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 9999 /* maximum input line length */

int mygetline(char **line);
char *mystrdup(char *s);

/* print the longest input line */
int main(int argc, char **argv)
{
	int n=10, i=0, j=0;
	char *line; /* current input line */
	char **lines;

	if (argc > 1)
		n = atoi(argv[1]);

	lines = (char **) malloc((n+1) * sizeof(char*));
	for (j=0;j<n;j++)
		lines[j] = NULL;

	while (mygetline(&line) > 0) {
		lines[i++] = mystrdup(line);
		free(line);

		if (i > n) {
			free(lines[0]);
			for (j=0;j<n;j++)
				lines[j] = lines[j+1];

			i = n;
		}
	}
	
	for (j=0;j<n;j++)
		if (lines[j] != NULL) printf("%s", lines[j]);

	return 0;
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
