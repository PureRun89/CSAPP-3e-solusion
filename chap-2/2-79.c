
int mul3div4(int x)
{
	int y = x >> 2 << 1 + x >> 2;
	int equiv_2 = (x & 3) == 2;
	int equiv_3 = (x & 3) == 3;
	return y + (-equiv_2) & 1 + (-equiv_3) & 2;
}
