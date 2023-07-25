
void *malloc(size_t size);
void *memset(void *s, int c, size_t n);

void *calloc(size_t nmemb, size_t size)
{
	if (((long) nmemb) * size > INT_MAX || nmemb == 0 || size == 0) return NULL;
	void *s = malloc(nmemb * size);
	memset(s, nmemb, size);
	return s;
}
