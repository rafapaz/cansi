#include <stdio.h>

void printbin(int n);
unsigned rotatebits(unsigned x, int n);

int main()
{
	unsigned x;
	int p, n;

	scanf("%u", &x);
	scanf("%d", &n);
	printbin(x);
	printbin(rotatebits(x,n));
	return 0;
}

unsigned rotatebits(unsigned x, int n)
{
	unsigned bit,r=x;

	while (n--) {
		bit = (r & 1) << 30;
		r = (r >> 1) | bit;
	}
	
	return r;
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
