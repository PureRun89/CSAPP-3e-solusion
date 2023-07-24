
int lower_one_mask(int n)
{
	int a = 1 << n - 1;
	a <<= 1;
	return a - 1;
}
