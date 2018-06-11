#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	void *p = NULL;
	printf("address:%d\n", p);
	printf("address+1:%d\n",p+sizeof(p));
	return 0;
}