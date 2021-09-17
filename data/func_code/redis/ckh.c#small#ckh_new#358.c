bool
ckh_new(tsd_t *tsd, ckh_t *ckh, size_t minitems, ckh_hash_t *hash,
    ckh_keycomp_t *keycomp) {
	bool ret;
	size_t mincells, usize;
	unsigned lg_mincells;

	assert(minitems > 0);
	assert(hash != NULL);
	assert(keycomp != NULL);

#ifdef CKH_COUNT
	ckh->ngrows = 0;
	ckh->nshrinks = 0;
	ckh->nshrinkfails = 0;
	ckh->ninserts = 0;
	ckh->nrelocs = 0;
#endif
	ckh->prng_state = 42; /* Value doesn't really matter. */
	ckh->count = 0;

	/*
	 * Find the minimum power of 2 that is large enough to fit minitems
	 * entries.  We are using (2+,2) cuckoo hashing, which has an expected
	 * maximum load factor of at least ~0.86, so 0.75 is a conservative load
	 * factor that will typically allow mincells items to fit without ever
	 * growing the table.
	 */
	assert(LG_CKH_BUCKET_CELLS > 0);
	mincells = ((minitems + (3 - (minitems % 3))) / 3) << 2;
	for (lg_mincells = LG_CKH_BUCKET_CELLS;
	    (ZU(1) << lg_mincells) < mincells;
	    lg_mincells++) {
		/* Do nothing. */
	}
	ckh->lg_minbuckets = lg_mincells - LG_CKH_BUCKET_CELLS;
	ckh->lg_curbuckets = lg_mincells - LG_CKH_BUCKET_CELLS;
	ckh->hash = hash;
	ckh->keycomp = keycomp;

	usize = sz_sa2u(sizeof(ckhc_t) << lg_mincells, CACHELINE);
	if (unlikely(usize == 0 || usize > LARGE_MAXCLASS)) {
		ret = true;
		goto label_return;
	}
	ckh->tab = (ckhc_t *)ipallocztm(tsd_tsdn(tsd), usize, CACHELINE, true,
	    NULL, true, arena_ichoose(tsd, NULL));
	if (ckh->tab == NULL) {
		ret = true;
		goto label_return;
	}

	ret = false;
label_return:
	return ret;
}
