bool
ckh_search(ckh_t *ckh, const void *searchkey, void **key, void **data) {
	size_t cell;

	assert(ckh != NULL);

	cell = ckh_isearch(ckh, searchkey);
	if (cell != SIZE_T_MAX) {
		if (key != NULL) {
			*key = (void *)ckh->tab[cell].key;
		}
		if (data != NULL) {
			*data = (void *)ckh->tab[cell].data;
		}
		return false;
	}

	return true;
}
