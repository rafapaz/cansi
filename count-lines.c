#include <stdio.h>

int main()
{
	int c, nl;

	nl=0;
	while ((c = getchar()) != EOF)
		nl += (c == '\n');
	printf("%d\n", nl);
	return 0;
}
