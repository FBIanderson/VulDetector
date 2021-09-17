static size_t
ckh_bucket_search(ckh_t *ckh, size_t bucket, const void *key) {
	ckhc_t *cell;
	unsigned i;

	for (i = 0; i < (ZU(1) << LG_CKH_BUCKET_CELLS); i++) {
		cell = &ckh->tab[(bucket << LG_CKH_BUCKET_CELLS) + i];
		if (cell->key != NULL && ckh->keycomp(key, cell->key)) {
			return (bucket << LG_CKH_BUCKET_CELLS) + i;
		}
	}

	return SIZE_T_MAX;
}
