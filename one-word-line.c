#include <stdio.h>

int main()
{
	int c, aux=0;

	while ((c = getchar()) != EOF) {
		if (!((aux == ' ' || aux == '\t' || aux == '\n') && (c == ' ' || c == '\t' || c == '\n')))
		{
			if (c == ' ' || c == '\t' || c == '\n')
				putchar('\n');
			else
				putchar(c);
		}
		aux = c;
	}
	return 0;
}
