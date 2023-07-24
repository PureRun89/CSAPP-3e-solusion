#include <stdio.h>

unsigned rotate_left(unsigned x, int n)
{
	int w = sizeof(int) << 3;
	unsigned ans = (x << n) + (x >> (w - n - !n));
	return ((-!!n) & ans) + ((-!n) & x);
}

int main()
{
	printf("%x\n", rotate_left(0x12345678, 0));
	printf("%x\n", rotate_left(0x12345678, 4));
	printf("%x\n", rotate_left(0x12345678, 20));
	printf("%x\n", rotate_left(0x12345678, 31));
	return 0;
}
