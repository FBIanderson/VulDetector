bool
ckh_iter(ckh_t *ckh, size_t *tabind, void **key, void **data) {
	size_t i, ncells;

	for (i = *tabind, ncells = (ZU(1) << (ckh->lg_curbuckets +
	    LG_CKH_BUCKET_CELLS)); i < ncells; i++) {
		if (ckh->tab[i].key != NULL) {
			if (key != NULL) {
				*key = (void *)ckh->tab[i].key;
			}
			if (data != NULL) {
				*data = (void *)ckh->tab[i].data;
			}
			*tabind = i + 1;
			return false;
		}
	}

	return true;
}
