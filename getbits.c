#include <stdio.h>

void printbin(int n);
unsigned getbits(unsigned x, int p, int n);

int main()
{
	int x = 8;
	int p = 3;
	int n = 2;
	printbin(x);
	printbin(p);
	printbin(n);
	printf("getbits(%d,%d,%d) = ", x,p,n);
	printbin(getbits(x,p,n));
	return 0;
}

unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

void printbin(int n)
{
  int c, k;
 
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
