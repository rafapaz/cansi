#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 9999 /* maximum input line length */

int mygetline(char **line);
void copy(char **to, char *from);

/* print the longest input line */
int main()
{
	int n=10, i=0, j=0;
	char *line; /* current input line */
	char **lines;

	lines = malloc((n+1) * sizeof(char*));
	for (j=0;j<n;j++)
		lines[j] = NULL;

	while (mygetline(&line) > 0) {
		lines[i++] = malloc(strlen(line)+1);
		strcpy(lines[i-1], line);
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
	*s = malloc((strlen(temp)+1) * sizeof(char));
	strcpy(*s, temp);
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char **to, char *from)
{
	int i=0;

	while ((*to[i] = from[i]) != '\0')
		++i;
}
