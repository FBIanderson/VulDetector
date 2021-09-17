static bool
ckh_rebuild(ckh_t *ckh, ckhc_t *aTab) {
	size_t count, i, nins;
	const void *key, *data;

	count = ckh->count;
	ckh->count = 0;
	for (i = nins = 0; nins < count; i++) {
		if (aTab[i].key != NULL) {
			key = aTab[i].key;
			data = aTab[i].data;
			if (ckh_try_insert(ckh, &key, &data)) {
				ckh->count = count;
				return true;
			}
			nins++;
		}
	}

	return false;
}
