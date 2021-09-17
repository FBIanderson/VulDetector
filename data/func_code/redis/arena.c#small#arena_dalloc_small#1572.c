void
arena_dalloc_small(tsdn_t *tsdn, void *ptr) {
	extent_t *extent = iealloc(tsdn, ptr);
	arena_t *arena = extent_arena_get(extent);

	arena_dalloc_bin(tsdn, arena, extent, ptr);
	arena_decay_tick(tsdn, arena);
}
