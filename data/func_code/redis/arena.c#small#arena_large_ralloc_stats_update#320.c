static void
arena_large_ralloc_stats_update(tsdn_t *tsdn, arena_t *arena, size_t oldusize,
    size_t usize) {
	arena_large_dalloc_stats_update(tsdn, arena, oldusize);
	arena_large_malloc_stats_update(tsdn, arena, usize);
}
