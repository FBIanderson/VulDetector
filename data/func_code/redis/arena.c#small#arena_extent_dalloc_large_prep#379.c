void
arena_extent_dalloc_large_prep(tsdn_t *tsdn, arena_t *arena, extent_t *extent) {
	if (config_stats) {
		arena_stats_lock(tsdn, &arena->stats);
		arena_large_dalloc_stats_update(tsdn, arena,
		    extent_usize_get(extent));
		arena_stats_unlock(tsdn, &arena->stats);
	}
	arena_nactive_sub(arena, extent_size_get(extent) >> LG_PAGE);
}
