void
arena_extent_ralloc_large_expand(tsdn_t *tsdn, arena_t *arena, extent_t *extent,
    size_t oldusize) {
	size_t usize = extent_usize_get(extent);
	size_t udiff = usize - oldusize;

	if (config_stats) {
		arena_stats_lock(tsdn, &arena->stats);
		arena_large_ralloc_stats_update(tsdn, arena, oldusize, usize);
		arena_stats_unlock(tsdn, &arena->stats);
	}
	arena_nactive_add(arena, udiff >> LG_PAGE);
}
