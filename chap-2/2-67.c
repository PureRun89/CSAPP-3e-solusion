#include <stdio.h>

int int_size_is_32()
{
	// This should run properly on 16-bit machines.
	unsigned a = 1 << 15;
	unsigned b = a << 1;
	a = b << 15;
	unsigned c = a << 1;
	return (!!b) & (!c) & (!!a); 
}


int main()
{
	printf("%d\n",int_size_is_32());
	return 0;
}
