static void
tcache_init(tsd_t *tsd, tcache_t *tcache, void *avail_stack) {
	memset(&tcache->link, 0, sizeof(ql_elm(tcache_t)));
	tcache->prof_accumbytes = 0;
	tcache->next_gc_bin = 0;
	tcache->arena = NULL;

	ticker_init(&tcache->gc_ticker, TCACHE_GC_INCR);

	size_t stack_offset = 0;
	assert((TCACHE_NSLOTS_SMALL_MAX & 1U) == 0);
	memset(tcache->bins_small, 0, sizeof(cache_bin_t) * NBINS);
	memset(tcache->bins_large, 0, sizeof(cache_bin_t) * (nhbins - NBINS));
	unsigned i = 0;
	for (; i < NBINS; i++) {
		tcache->lg_fill_div[i] = 1;
		stack_offset += tcache_bin_info[i].ncached_max * sizeof(void *);
		/*
		 * avail points past the available space.  Allocations will
		 * access the slots toward higher addresses (for the benefit of
		 * prefetch).
		 */
		tcache_small_bin_get(tcache, i)->avail =
		    (void **)((uintptr_t)avail_stack + (uintptr_t)stack_offset);
	}
	for (; i < nhbins; i++) {
		stack_offset += tcache_bin_info[i].ncached_max * sizeof(void *);
		tcache_large_bin_get(tcache, i)->avail =
		    (void **)((uintptr_t)avail_stack + (uintptr_t)stack_offset);
	}
	assert(stack_offset == stack_nelms * sizeof(void *));
}
