#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */

int mygetline(char **line);
void copy(char **to, char **from);

/* print the longest input line */
int main()
{
	int n=10, i=0, j=0;
	char *line; /* current input line */
	char **lines;

	lines = malloc((n+1) * sizeof(char*));

	while (mygetline(&line) > 0) {
		lines[i++] = malloc(strlen(line)+1);
		copy(&lines[i-1], &line);
		free(line);

		if (i > n) {
			free(lines[0]);
			for (j=0;j<n;j++)
				lines[j] = lines[j+1];

			i = n;
		}
	}
	
	for (j=0;j<n;j++)
		printf("%s", lines[j]);

	return 0;
}

/* mygetline: read a line into s, return length */
int mygetline(char **s)
{
	int c, i;

	*s = malloc(sizeof(char));
	for (i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
		realloc(*s, sizeof(char)*(i+1));
		*s[i] = c;
	}
	if (c == '\n') {
		realloc(*s, sizeof(char)*(i+1));
		*s[i] = c;
		++i;
	}

	realloc(s, sizeof(char)*(i+1));
	s[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char **to, char **from)
{
	int i=0;

	while ((*to[i] = *from[i]) != '\0')
		++i;
}
