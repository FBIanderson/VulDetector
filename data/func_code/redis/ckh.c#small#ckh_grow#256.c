static bool
ckh_grow(tsd_t *tsd, ckh_t *ckh) {
	bool ret;
	ckhc_t *tab, *ttab;
	unsigned lg_prevbuckets, lg_curcells;

#ifdef CKH_COUNT
	ckh->ngrows++;
#endif

	/*
	 * It is possible (though unlikely, given well behaved hashes) that the
	 * table will have to be doubled more than once in order to create a
	 * usable table.
	 */
	lg_prevbuckets = ckh->lg_curbuckets;
	lg_curcells = ckh->lg_curbuckets + LG_CKH_BUCKET_CELLS;
	while (true) {
		size_t usize;

		lg_curcells++;
		usize = sz_sa2u(sizeof(ckhc_t) << lg_curcells, CACHELINE);
		if (unlikely(usize == 0 || usize > LARGE_MAXCLASS)) {
			ret = true;
			goto label_return;
		}
		tab = (ckhc_t *)ipallocztm(tsd_tsdn(tsd), usize, CACHELINE,
		    true, NULL, true, arena_ichoose(tsd, NULL));
		if (tab == NULL) {
			ret = true;
			goto label_return;
		}
		/* Swap in new table. */
		ttab = ckh->tab;
		ckh->tab = tab;
		tab = ttab;
		ckh->lg_curbuckets = lg_curcells - LG_CKH_BUCKET_CELLS;

		if (!ckh_rebuild(ckh, tab)) {
			idalloctm(tsd_tsdn(tsd), tab, NULL, NULL, true, true);
			break;
		}

		/* Rebuilding failed, so back out partially rebuilt table. */
		idalloctm(tsd_tsdn(tsd), ckh->tab, NULL, NULL, true, true);
		ckh->tab = tab;
		ckh->lg_curbuckets = lg_prevbuckets;
	}

	ret = false;
label_return:
	return ret;
}
