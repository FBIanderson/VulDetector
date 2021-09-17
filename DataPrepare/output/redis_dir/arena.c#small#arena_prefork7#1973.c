void
arena_prefork7(tsdn_t *tsdn, arena_t *arena) {
	for (unsigned i = 0; i < NBINS; i++) {
		bin_prefork(tsdn, &arena->bins[i]);
	}
}
