#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int mygetline(char line[], int maxline);
void reverse(char s[]);
void myputline(char line[]);

/* print the longest input line */
int main()
{
	int len; /* current line length */
	char line[MAXLINE]; /* current input line */
	char longest[MAXLINE]; /* longest line saved here */

	while ((len = mygetline(line, MAXLINE)) > 0) {
		reverse(line);
		myputline(line);
	}
	return 0;
}

/* mygetline: read a line into s, return length */
int mygetline(char s[],int lim)
{
	int c, i;

	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	return i;
}

void myputline(char line[])
{
	int i=0;

	while (line[i++] != '\0')
		putchar(line[i-1]);
}

void reverse(char s[])
{
	int i=0,j=0,len=0,aux=0;

	while (s[i++] != '\0');
	len = i-1;
	i -= 2;
	while (i > len/2) {
		aux = s[i];
		s[i--] = s[j];
		s[j++] = aux;
	}
}
