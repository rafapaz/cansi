#include <stdio.h>

#define OUT 0
#define IN_LINE 1
#define IN_MULTI 2
#define IN_ALMOST 3
#define MAX 9999

int main()
{
	int c, ant, state;

	ant = 0;
	state = OUT;
	while ((c = getchar()) != EOF) {
		if (state==IN_ALMOST && c == '*')
			state = IN_MULTI;
		else if (state==IN_ALMOST && c == '/')
			state = IN_LINE;

		if ((state==IN_LINE && (c == '\n')) || (state==IN_MULTI && (ant == '*' && c == '/')))
			state = OUT;
		else if (state == OUT && c == '/')
			state = IN_ALMOST;
		else if (state == IN_ALMOST) {
			putchar('/');
			putchar(c);
			state = OUT;
		} else if (state == OUT)
			putchar(c);

		ant=c;
	}

	return 0;
}
