
int saturating_add(int x, int y)
{
	int z = x + y;
	int magic = 1 << (8*sizeof(int)-1);
	int neg_x = (x & magic) == magic;
	int neg_y = (y & magic) == magic;
	int neg_z = (z & magic) == magic;
	int b1 = (neg_x == 0) & (neg_y == 0) & (neg_z == 1);
	int b2 = (neg_x == 1) & (neg_y == 1) & (neg_z == 0);
	return (-!(b1 | b2)) & z + (-b1) & INT_MAX + (-b2) & INT_MIN;
}
