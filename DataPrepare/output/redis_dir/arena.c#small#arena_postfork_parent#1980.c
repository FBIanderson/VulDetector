void
arena_postfork_parent(tsdn_t *tsdn, arena_t *arena) {
	unsigned i;

	for (i = 0; i < NBINS; i++) {
		bin_postfork_parent(tsdn, &arena->bins[i]);
	}
	malloc_mutex_postfork_parent(tsdn, &arena->large_mtx);
	base_postfork_parent(tsdn, arena->base);
	malloc_mutex_postfork_parent(tsdn, &arena->extent_avail_mtx);
	extents_postfork_parent(tsdn, &arena->extents_dirty);
	extents_postfork_parent(tsdn, &arena->extents_muzzy);
	extents_postfork_parent(tsdn, &arena->extents_retained);
	malloc_mutex_postfork_parent(tsdn, &arena->extent_grow_mtx);
	malloc_mutex_postfork_parent(tsdn, &arena->decay_dirty.mtx);
	malloc_mutex_postfork_parent(tsdn, &arena->decay_muzzy.mtx);
	if (config_stats) {
		malloc_mutex_postfork_parent(tsdn, &arena->tcache_ql_mtx);
	}
}
