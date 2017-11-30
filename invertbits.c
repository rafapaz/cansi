#include <stdio.h>

void printbin(int n);
unsigned invert(unsigned x, int p, int n);

int main()
{
	unsigned x;
	int p, n;

	scanf("%u", &x);
	scanf("%d", &p);
	scanf("%d", &n);
	printbin(x);
	printbin(invert(x,p,n));
	return 0;
}

unsigned invert(unsigned x, int p, int n)
{
	int mask = (((x >> (p+1-n)) & ~(~0 << n)) | ~(~0 << n)) << (p+1-n); // [0000][1111][0000]
	return x ^ mask;

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
