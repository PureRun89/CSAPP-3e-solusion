
int signed_high_prod(int x, int y);

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
	int z = signed_high_prod(x, y);
	int magic = 1 << (sizeof(int)<<3) - 1;
	int neg_x = (x & magic) == magic;
	int neg_y = (y & magic) == magic;
	return z + x * neg_y + y * neg_x;
}
