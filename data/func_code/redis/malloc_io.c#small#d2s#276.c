static char *
d2s(intmax_t x, char sign, char *s, size_t *slen_p) {
	bool neg;

	if ((neg = (x < 0))) {
		x = -x;
	}
	s = u2s(x, 10, false, s, slen_p);
	if (neg) {
		sign = '-';
	}
	switch (sign) {
	case '-':
		if (!neg) {
			break;
		}
		/* Fall through. */
	case ' ':
	case '+':
		s--;
		(*slen_p)++;
		*s = sign;
		break;
	default: not_reached();
	}
	return s;
}
