static inline void
swapfunc(char *a, char *b, size_t n, int swaptype)
{

	if (swaptype <= 1)
		swapcode(long, a, b, n)
	else
		swapcode(char, a, b, n)
}
