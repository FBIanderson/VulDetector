static void
tcache_destroy(tsd_t *tsd, tcache_t *tcache, bool tsd_tcache) {
	tcache_flush_cache(tsd, tcache);
	tcache_arena_dissociate(tsd_tsdn(tsd), tcache);

	if (tsd_tcache) {
		/* Release the avail array for the TSD embedded auto tcache. */
		void *avail_array =
		    (void *)((uintptr_t)tcache_small_bin_get(tcache, 0)->avail -
		    (uintptr_t)tcache_bin_info[0].ncached_max * sizeof(void *));
		idalloctm(tsd_tsdn(tsd), avail_array, NULL, NULL, true, true);
	} else {
		/* Release both the tcache struct and avail array. */
		idalloctm(tsd_tsdn(tsd), tcache, NULL, NULL, true, true);
	}
}
