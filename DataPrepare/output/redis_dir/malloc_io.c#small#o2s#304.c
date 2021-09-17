static char *
o2s(uintmax_t x, bool alt_form, char *s, size_t *slen_p) {
	s = u2s(x, 8, false, s, slen_p);
	if (alt_form && *s != '0') {
		s--;
		(*slen_p)++;
		*s = '0';
	}
	return s;
}
