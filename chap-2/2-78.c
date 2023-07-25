
int divide_power2(int x, int k)
{
	int magic = 1 << (sizeof(int)<<3) - 1;
	int neg_x = (x & magic) == magic;
	int ans1 = x >> k;
	int ans2 = (x + (1 << k) - 1) >> k;
	return (-!neg_x) & ans1 + (-neg_x) & ans2;
}
