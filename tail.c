#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* maximum input line length */

int mygetline(char *line);
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
	int n=10;
	char *line; /* current input line */
	char **lines;

	line = malloc(sizeof(char));
	lines = malloc(n * sizeof(*char));

	while (mygetline(line) > 0) {
		lines[n--] = malloc(strlen(line)+1);
		free(line);
	}
		
	//printf("%s", line);

	return 0;
}

/* mygetline: read a line into s, return length */
int mygetline(char *s)
{
	int c, i;

	for (i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
		realloc(s, sizeof(char)*(i+1));
		s[i] = c;
	}
	if (c == '\n') {
		realloc(s, sizeof(char)*(i+1));
		s[i] = c;
		++i;
	}

	realloc(s, sizeof(char)*(i+1));
	s[i] = '\0';
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i=0;

	while ((to[i] = from[i]) != '\0')
		++i;
}
