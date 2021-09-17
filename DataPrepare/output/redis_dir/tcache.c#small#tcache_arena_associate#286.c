void
tcache_arena_associate(tsdn_t *tsdn, tcache_t *tcache, arena_t *arena) {
	assert(tcache->arena == NULL);
	tcache->arena = arena;

	if (config_stats) {
		/* Link into list of extant tcaches. */
		malloc_mutex_lock(tsdn, &arena->tcache_ql_mtx);

		ql_elm_new(tcache, link);
		ql_tail_insert(&arena->tcache_ql, tcache, link);
		cache_bin_array_descriptor_init(
		    &tcache->cache_bin_array_descriptor, tcache->bins_small,
		    tcache->bins_large);
		ql_tail_insert(&arena->cache_bin_array_descriptor_ql,
		    &tcache->cache_bin_array_descriptor, link);

		malloc_mutex_unlock(tsdn, &arena->tcache_ql_mtx);
	}
}
