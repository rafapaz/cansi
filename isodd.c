#include <stdio.h>

void printbin(int n);
unsigned isodd(unsigned x);

int main()
{
	int x;
	scanf("%d", &x);
	printbin(x);
	printf("is odd? %d\n", isodd(x));
	return 0;
}

unsigned isodd(unsigned x)
{
	return (x & 1);
}

void printbin(int n)
{
  int c, k;
 
  printf("%d : ", n);
  for (c = 31; c >= 0; c--)
  {
    k = n >> c;
 
    if (k & 1)
      printf("1");
    else
      printf("0");
  }
 
  printf("\n");
}
