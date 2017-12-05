#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 999
char buf[BUFSIZE];
int bufp = 0;

int getint(int *pn);
int getch(void);
void ungetch(int);

int getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;
	while (isspace(c = getch())); /* skip white space */
		
	while (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		//ungetch(c); /* it is not a number */
		c = getch();
		//return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * (*pn) + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main()
{
	int *pn = malloc(sizeof(int));

	//while (getint(pn) != EOF);
	getint(pn);

	printf("%d", *pn);

	return 0;
}
