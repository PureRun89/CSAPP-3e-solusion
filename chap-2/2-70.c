#include <stdio.h>


int fits_bits(int x, int n)
{
	int w = sizeof(int) << 3;
	int neg = ((x & (1 << (8*sizeof(int)-1))) == (1 << (8*sizeof(int)-1)));
	unsigned y = x;
	y = ((-!neg) & y) + ((-neg) & (-y - 1));
	//printf("%d %x %x\n",neg,y,(1 << (8*sizeof(int)-1)));
	//printf("%d \n",(x & (1 << (8*sizeof(int)-1)))==(1 << (8*sizeof(int)-1)) );
	return (y >> (n - 1)) == 0;
}


int main()
{
	printf("%d\n", fits_bits(0xFFFFFFFE, 2));
	printf("%d\n", fits_bits(0xFFFFFFFD, 2));
	printf("%d\n", fits_bits(0x00000002, 2));
	printf("%d\n", fits_bits(0x80000000, 32));
	return 0;
}
