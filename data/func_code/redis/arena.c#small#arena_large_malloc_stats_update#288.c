static void
arena_large_malloc_stats_update(tsdn_t *tsdn, arena_t *arena, size_t usize) {
	szind_t index, hindex;

	cassert(config_stats);

	if (usize < LARGE_MINCLASS) {
		usize = LARGE_MINCLASS;
	}
	index = sz_size2index(usize);
	hindex = (index >= NBINS) ? index - NBINS : 0;

	arena_stats_add_u64(tsdn, &arena->stats,
	    &arena->stats.lstats[hindex].nmalloc, 1);
}
