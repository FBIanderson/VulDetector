static char *
x2s(uintmax_t x, bool alt_form, bool uppercase, char *s, size_t *slen_p) {
	s = u2s(x, 16, uppercase, s, slen_p);
	if (alt_form) {
		s -= 2;
		(*slen_p) += 2;
		memcpy(s, uppercase ? "0X" : "0x", 2);
	}
	return s;
}
