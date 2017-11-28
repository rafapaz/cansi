#include <stdio.h>

void printbin(int n);

int main()
{
	printbin(293); 
	return 0;
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
