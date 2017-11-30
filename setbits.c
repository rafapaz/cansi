#include <stdio.h>

void printbin(int n);
unsigned setbits(unsigned x, int p, int n, int y);

int main()
{
	unsigned x;
	int p, n, y;

	scanf("%u", &x);
	scanf("%d", &y);
	scanf("%d", &p);
	scanf("%d", &n);
	printbin(x);
	printbin(y);
	printbin(setbits(x,p,n,y));
	return 0;
}

unsigned setbits(unsigned x, int p, int n, int y)
{
	return (((x >> (p+1-n)) | (y & ~(~0 << n))) << (p+1-n)) | (x & ~(~0 << (p+1-n)));
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
