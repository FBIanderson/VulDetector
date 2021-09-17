void
ckh_delete(tsd_t *tsd, ckh_t *ckh) {
	assert(ckh != NULL);

#ifdef CKH_VERBOSE
	malloc_printf(
	    "%s(%p): ngrows: %"FMTu64", nshrinks: %"FMTu64","
	    " nshrinkfails: %"FMTu64", ninserts: %"FMTu64","
	    " nrelocs: %"FMTu64"\n", __func__, ckh,
	    (unsigned long long)ckh->ngrows,
	    (unsigned long long)ckh->nshrinks,
	    (unsigned long long)ckh->nshrinkfails,
	    (unsigned long long)ckh->ninserts,
	    (unsigned long long)ckh->nrelocs);
#endif

	idalloctm(tsd_tsdn(tsd), ckh->tab, NULL, NULL, true, true);
	if (config_debug) {
		memset(ckh, JEMALLOC_FREE_JUNK, sizeof(ckh_t));
	}
}
