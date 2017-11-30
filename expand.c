#include <stdio.h>
#include <stdlib.h>

#define MAX 9999

char *expande(char *s1, char *s2);

int main()
{
	char s1[MAX], s2[MAX];

	scanf("%s", s1);
	printf("%s", expande(s1,s2));
	return 0;
}

char *expande(char *s1, char *s2)
{
	int i=0,j=0,c=0,inf=0,sup=0,k=0;
	
	while (c = s1[i++]) {
		if (c == '-') {
			inf = s1[i-1];
			sup = s1[i+1];
		}

		if (sup!=0) {
			for (j=inf;j <= sup;j++,k++) {
				s2[k] = j;
			}
			inf = sup = 0;
		}
	}
	s2[k] = '\0';
	return s2;
}
