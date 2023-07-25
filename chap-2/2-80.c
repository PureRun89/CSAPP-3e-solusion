
int threefourths(int x)
{
	// We call mul3div4 from 2.79
	int y = mul3div4(x);
	int magic = 1 << (sizeof(int)<<3) - 1;
	int neg_x = (x & magic) == magic;
	int multi_of_4 = (x & 3) == 0;
	int check = (!neg_x) | multi_of_4;
	return (-!check) & y + (-check) & (y + 1);
}
