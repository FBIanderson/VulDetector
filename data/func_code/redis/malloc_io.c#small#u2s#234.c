static char *
u2s(uintmax_t x, unsigned base, bool uppercase, char *s, size_t *slen_p) {
	unsigned i;

	i = U2S_BUFSIZE - 1;
	s[i] = '\0';
	switch (base) {
	case 10:
		do {
			i--;
			s[i] = "0123456789"[x % (uint64_t)10];
			x /= (uint64_t)10;
		} while (x > 0);
		break;
	case 16: {
		const char *digits = (uppercase)
		    ? "0123456789ABCDEF"
		    : "0123456789abcdef";

		do {
			i--;
			s[i] = digits[x & 0xf];
			x >>= 4;
		} while (x > 0);
		break;
	} default: {
		const char *digits = (uppercase)
		    ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		    : "0123456789abcdefghijklmnopqrstuvwxyz";

		assert(base >= 2 && base <= 36);
		do {
			i--;
			s[i] = digits[x % (uint64_t)base];
			x /= (uint64_t)base;
		} while (x > 0);
	}}

	*slen_p = U2S_BUFSIZE - 1 - i;
	return &s[i];
}
