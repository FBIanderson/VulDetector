bool
ckh_insert(tsd_t *tsd, ckh_t *ckh, const void *key, const void *data) {
	bool ret;

	assert(ckh != NULL);
	assert(ckh_search(ckh, key, NULL, NULL));

#ifdef CKH_COUNT
	ckh->ninserts++;
#endif

	while (ckh_try_insert(ckh, &key, &data)) {
		if (ckh_grow(tsd, ckh)) {
			ret = true;
			goto label_return;
		}
	}

	ret = false;
label_return:
	return ret;
}
