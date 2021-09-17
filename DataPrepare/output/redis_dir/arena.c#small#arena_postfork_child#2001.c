void
arena_postfork_child(tsdn_t *tsdn, arena_t *arena) {
	unsigned i;

	atomic_store_u(&arena->nthreads[0], 0, ATOMIC_RELAXED);
	atomic_store_u(&arena->nthreads[1], 0, ATOMIC_RELAXED);
	if (tsd_arena_get(tsdn_tsd(tsdn)) == arena) {
		arena_nthreads_inc(arena, false);
	}
	if (tsd_iarena_get(tsdn_tsd(tsdn)) == arena) {
		arena_nthreads_inc(arena, true);
	}
	if (config_stats) {
		ql_new(&arena->tcache_ql);
		ql_new(&arena->cache_bin_array_descriptor_ql);
		tcache_t *tcache = tcache_get(tsdn_tsd(tsdn));
		if (tcache != NULL && tcache->arena == arena) {
			ql_elm_new(tcache, link);
			ql_tail_insert(&arena->tcache_ql, tcache, link);
			cache_bin_array_descriptor_init(
			    &tcache->cache_bin_array_descriptor,
			    tcache->bins_small, tcache->bins_large);
			ql_tail_insert(&arena->cache_bin_array_descriptor_ql,
			    &tcache->cache_bin_array_descriptor, link);
		}
	}

	for (i = 0; i < NBINS; i++) {
		bin_postfork_child(tsdn, &arena->bins[i]);
	}
	malloc_mutex_postfork_child(tsdn, &arena->large_mtx);
	base_postfork_child(tsdn, arena->base);
	malloc_mutex_postfork_child(tsdn, &arena->extent_avail_mtx);
	extents_postfork_child(tsdn, &arena->extents_dirty);
	extents_postfork_child(tsdn, &arena->extents_muzzy);
	extents_postfork_child(tsdn, &arena->extents_retained);
	malloc_mutex_postfork_child(tsdn, &arena->extent_grow_mtx);
	malloc_mutex_postfork_child(tsdn, &arena->decay_dirty.mtx);
	malloc_mutex_postfork_child(tsdn, &arena->decay_muzzy.mtx);
	if (config_stats) {
		malloc_mutex_postfork_child(tsdn, &arena->tcache_ql_mtx);
	}
}
