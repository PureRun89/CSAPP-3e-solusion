#include <stdio.h>


unsigned srl(unsigned x, int k)
{
	/* Perform shift arithmetically */
	unsigned xsra = (int) x >> k;
	int neg = ((x & (1 << (8*sizeof(int)-1))) == (1 << (8*sizeof(int)-1)));
	int ans1 = (xsra & ((neg << (8*sizeof(int)-k)) - 1));
	return ((-!!k) & ans1) + ((-!k) & x);
}


int sra(int x, int k)
{
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;
	int neg = ((x & (1 << (8*sizeof(int)-1))) == (1 << (8*sizeof(int)-1)));
	int ans1 = (xsrl | ((((1 << k) - 1) << (8*sizeof(int) - k))) & (-neg));
	return ((-!!k) & ans1) + ((-!k) & x);
}


int main()
{
	printf("%x\n", sra(0x8FFFFFFE,4));
	return 0;
}
