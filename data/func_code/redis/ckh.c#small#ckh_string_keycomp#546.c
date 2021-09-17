bool
ckh_string_keycomp(const void *k1, const void *k2) {
	assert(k1 != NULL);
	assert(k2 != NULL);

	return !strcmp((char *)k1, (char *)k2);
}
