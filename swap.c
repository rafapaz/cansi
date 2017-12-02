#include <stdio.h>

#define swap(t,x,y) do{  t temp=x; x=y; y=temp; } while(0)

int main()
{
	int x,y;
	scanf("%d", &x);
	scanf("%d", &y);
	printf("x = %d, y = %d \n", x, y);
	swap(int,x,y);
	printf("x = %d, y = %d \n", x, y);

	return 0;
}
