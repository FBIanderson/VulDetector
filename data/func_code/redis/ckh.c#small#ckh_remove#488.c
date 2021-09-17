bool
ckh_remove(tsd_t *tsd, ckh_t *ckh, const void *searchkey, void **key,
    void **data) {
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
		ckh->tab[cell].key = NULL;
		ckh->tab[cell].data = NULL; /* Not necessary. */

		ckh->count--;
		/* Try to halve the table if it is less than 1/4 full. */
		if (ckh->count < (ZU(1) << (ckh->lg_curbuckets
		    + LG_CKH_BUCKET_CELLS - 2)) && ckh->lg_curbuckets
		    > ckh->lg_minbuckets) {
			/* Ignore error due to OOM. */
			ckh_shrink(tsd, ckh);
		}

		return false;
	}

	return true;
}
