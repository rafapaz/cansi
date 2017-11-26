#include <stdio.h>

int main()
{
	int c, aux=0;

	while ((c = getchar()) != EOF) {
		if (!(aux == ' ' && c == ' '))
			putchar(c);
		aux = c;
	}
	return 0;
}
