static void
tcache_flush_cache(tsd_t *tsd, tcache_t *tcache) {
	assert(tcache->arena != NULL);

	for (unsigned i = 0; i < NBINS; i++) {
		cache_bin_t *tbin = tcache_small_bin_get(tcache, i);
		tcache_bin_flush_small(tsd, tcache, tbin, i, 0);

		if (config_stats) {
			assert(tbin->tstats.nrequests == 0);
		}
	}
	for (unsigned i = NBINS; i < nhbins; i++) {
		cache_bin_t *tbin = tcache_large_bin_get(tcache, i);
		tcache_bin_flush_large(tsd, tbin, i, 0, tcache);

		if (config_stats) {
			assert(tbin->tstats.nrequests == 0);
		}
	}

	if (config_prof && tcache->prof_accumbytes > 0 &&
	    arena_prof_accum(tsd_tsdn(tsd), tcache->arena,
	    tcache->prof_accumbytes)) {
		prof_idump(tsd_tsdn(tsd));
	}
}
