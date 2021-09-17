void *
tcache_alloc_small_hard(tsdn_t *tsdn, arena_t *arena, tcache_t *tcache,
    cache_bin_t *tbin, szind_t binind, bool *tcache_success) {
	void *ret;

	assert(tcache->arena != NULL);
	arena_tcache_fill_small(tsdn, arena, tcache, tbin, binind,
	    config_prof ? tcache->prof_accumbytes : 0);
	if (config_prof) {
		tcache->prof_accumbytes = 0;
	}
	ret = cache_bin_alloc_easy(tbin, tcache_success);

	return ret;
}
