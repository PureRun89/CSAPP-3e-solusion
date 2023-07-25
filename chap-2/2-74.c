
int tsub_ok(int x, int y)
{
	int z = x - y;
	int magic = 1 << (sizeof(int)<<3) - 1;
	int neg_x = (x & magic) == magic;
	int neg_y = (y & magic) == magic;
	int neg_z = (z & magic) == magic;
	return (neg_x ^ neg_y) & (neg_x ^ neg_z);
}
