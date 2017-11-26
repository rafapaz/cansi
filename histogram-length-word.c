#include <stdio.h>

#define IN 1
#define OUT 0
#define MAX 9999

int main()
{
	int i, c, wl, state;
	int lengths[MAX];

	for (i=0; i < MAX; i++)
		lengths[i] = 0;

	state = OUT;
	wl = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
		} else if (state == OUT && !(c == ' ' || c == '\n' || c == '\t')) {
			state = IN;
			lengths[wl]++;
			wl = 1;
		} else if (state == IN) {
			wl++;
		}
	}

	for (i=1; i < MAX; i++) {
		if (lengths[i])
			printf("%d: %d\n", i, lengths[i]);
	}

	return 0;
}
